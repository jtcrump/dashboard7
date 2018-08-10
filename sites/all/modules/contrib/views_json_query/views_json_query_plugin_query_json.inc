<?php
/**
 * @file
 * Query plugin for views_json_query.
 */

class views_json_query_plugin_query_json extends views_plugin_query {

  /**
   * Generate a query from all of the information supplied to the object.
   *
   * @param $get_count
   *   Provide a countquery if this is true, otherwise provide a normal query.
   */
  function query($get_count = FALSE) {
    $filters = array();

    if (isset($this->filter)) {
      foreach ($this->filter as $filter) {
        // set the filter value for grouped filters
        $filter->options['value'] = $filter->value;
        if ($filter instanceof views_json_query_handler_filter) {
          $filters[] = $filter->generate();
        }
      }
    }
    // @todo Add an option for the filters to be 'and' or 'or'.
    return $filters;
  }

  /**
   * Builds the necessary info to execute the query.
   */
  function build(&$view) {
    $view->init_pager();

    // Let the pager modify the query to add limits.
    $this->pager->query();

    // Build the JSON file URL.
    $json_file = $this->options['json_file'];

    if (!empty($view->build_info['substitutions'])) {
      $json_file = strtr($json_file, $view->build_info['substitutions']);
    }

    $parsed = parse_url($json_file);
    $query_string = drupal_get_query_array(isset($parsed['query']) ? $parsed['query'] : array());

    // Add query string parameters from filters.
    if (isset($this->query_string)) {
      foreach ($this->query_string as $k => $v) {
        $query_string[$k] = $v;
      }
    }

    // Add pagination query string argument.
    if ($this->options['enable_pagination_query_parameters']) {
      if (isset($view->query->offset)) {
        $query_string[$this->options['pagination_offset_query_parameter']] = $view->query->offset;
      }

      if (isset($view->query->limit)) {
        $query_string[$this->options['pagination_limit_query_parameter']] = $view->query->limit;
      }
    }

    // Rebuild the JSON file URL.
    $view->query->options['json_file'] = "{$parsed['scheme']}://{$parsed['host']}{$parsed['path']}?" . drupal_http_build_query($query_string);
    
    $view->build_info['query'] = $this->query();
    $view->build_info['query_args'] = array();
  }

  /**
   * Fetch file.
   */
  function fetch_file($uri) {
    $parsed = parse_url($uri);
    // Check for local file.
    if (empty($parsed['host'])) {
      if (!file_exists($uri)) {
        throw new Exception(t('Local file not found.'));
      }
      return file_get_contents($uri);
    }

    $destination = 'public://views_json_query';
    if (!file_prepare_directory($destination, FILE_CREATE_DIRECTORY |
      FILE_MODIFY_PERMISSIONS)) {
      throw new Exception(
        t('Files directory either cannot be created or is not writable.')
      );
    }

    $headers = array();
    $cache_file = 'views_json_query_' . md5($uri);
    if ($cache = cache_get($cache_file)) {
      $last_headers = $cache->data;

      if (!empty($last_headers['etag'])) {
        $headers['If-None-Match'] = $last_headers['etag'];
      }
      if (!empty($last_headers['last-modified'])) {
        $headers['If-Modified-Since'] = $last_headers['last-modified'];
      }
    }

    // Rebuild the JSON file URL.
    $request_options = array('headers' => $headers);
    $request_context_options = array();

    if (parse_url($uri, PHP_URL_SCHEME) == 'https') {
      foreach ($this->options as $option => $value) {
        if (strpos($option, 'ssl_') === 0 && $value) {
          $request_context_options['ssl'][substr($option, 4)] = $value;
        }
      }
    }

    if ($request_context_options) {
      $request_options['context'] =  stream_context_create($request_context_options);
    }

    $result = drupal_http_request($uri, $request_options);

    if (isset($result->error)) {
      $args = array('%error' => $result->error, '%uri' => $uri);
      $message = t('HTTP response: %error. URI: %uri', $args);
      throw new Exception($message);
    }

    $cache_file_uri = "$destination/$cache_file";

    if ($result->code == 304) {
      if (file_exists($cache_file_uri)) {
        return file_get_contents($cache_file_uri);
      }
      // We have the headers but no cache file. :(
      // Run it back.
      cache_clear_all($cache_file, 'cache');
      return $this->fetch_file($uri);
    }

    // As learned from Feeds caching mechanism, save to file.
    file_unmanaged_save_data($result->data, $cache_file_uri, FILE_EXISTS_REPLACE);
    cache_set($cache_file, $result->headers);
    return $result->data;
  }

  /**
   * Execute.
   */
  function execute(&$view) {
    $start = microtime(TRUE);

    // Avoid notices about $view->execute_time being undefined if the query
    // doesn't finish.
    $view->execute_time = NULL;

    // Make sure that an xml file exists.
    // This could happen if you come from the add wizard to the actual views
    // edit page.
    if (empty($this->options['json_file'])) {
      return FALSE;
    }

    $data = new stdClass();
    try {
      $data->contents = $this->fetch_file($this->options['json_file']);
    }
    catch (Exception $e) {
      if ($this->options['show_errors']) {
        drupal_set_message(
          t('Views Json Query') . ': ' . $e->getMessage(), 'error'
        );
      }
      return;
    }

    // When content is empty, parsing it is pointless.
    if (!$data->contents) {
      if ($this->options['show_errors']) {
        drupal_set_message(t('Views Json Backend: File is empty.'), 'warning');
      }
      return;
    }

    // Go!
    $ret = $this->parse($view, $data);
    $view->execute_time = microtime(TRUE) - $start;

    if (!$ret) {
      if (version_compare(phpversion(), '5.3.0', '>=')) {
        $tmp = array(
          JSON_ERROR_NONE =>
          t('No error has occurred'),
          JSON_ERROR_DEPTH =>
          t('The maximum stack depth has been exceeded'),
          JSON_ERROR_STATE_MISMATCH =>
          t('Invalid or malformed JSON'),
          JSON_ERROR_CTRL_CHAR =>
          t('Control character error, possibly incorrectly encoded'),
          JSON_ERROR_SYNTAX =>
          t('Syntax error'),
          JSON_ERROR_UTF8 =>
          t('Malformed UTF-8 characters, possibly incorrectly encoded'),
        );
        if (json_last_error() != 0) {
          $msg = $tmp[json_last_error()] . ' - ' . $this->options['json_file'];
          drupal_set_message($msg, 'error');
        }
      }
      else {
        drupal_set_message(t(
          'Views Json Backend: Parse json error') .
          ' - ' . $this->options['json_file'], 'error'
        );
      }
    }
  }

  /**
   * Fetch data in array according to apath.
   *
   * @param string $apath
   *   Something like '1/name/0'
   *
   * @param array $array
   *
   * @return array
   */
  function apath($apath, $array) {
    $r = & $array;
    $paths = explode('/', trim($apath, '//'));
    foreach ($paths as $path) {
      if (is_array($r) && isset($r[$path])) {
        $r = & $r[$path];
      }
      elseif (is_object($r)) {
        $r = & $r->$path;
      }
      else {
        break;
      }
    }

    return $r;
  }

  /**
   * Define ops for using in filter.
   */
  function ops($op, $l, $r) {
    $table = array(
      '=' => create_function('$l,$r', 'return $l === $r;'),
      'not empty' => create_function('$l,$r', 'return !empty($l);'),
      '!=' => create_function('$l,$r', 'return $l !== $r;'),
      'contains' => create_function('$l, $r', 'return strpos($l, $r) !== false;'),
      '!contains' => create_function('$l, $r', 'return strpos($l, $r) === false;'),
      'shorterthan' => create_function('$l, $r', 'return strlen($l) < $r;'),
      'longerthan' => create_function('$l, $r', 'return strlen($l) > $r;'),
    );

    return call_user_func_array($table[$op], array($l, $r));
  }

  /**
   * Parse.
   */
  function parse(&$view, $data) {
    $ret = json_decode($data->contents, FALSE);
    if (!$ret) {
      return FALSE;
    }

    // Get rows.
    $rows = $this->apath($this->options['row_apath'], $ret);

    // Filter.
    foreach ($rows as $k => $row) {
      $check = TRUE;
      foreach ($view->build_info['query'] as $filter) {
        $l = is_object($row) ? $row->{$filter[0]} : $row[$filter[0]];
        $check = $this->ops($filter[1], $l, $filter[2]);
        if (!$check) {
          break;
        }
      }
      if (!$check) {
        unset($rows[$k]);
      }
    }

    try {
      if ($this->pager->use_count_query() || !empty($view->get_total_rows)) {
        if (!empty($this->options['total_items_apath'])) {
          $this->pager->total_items = $this->apath($this->options['total_items_apath'], $ret);
        }
        else {
          // Hackish execute_count_query implementation.
          $this->pager->total_items = count($rows);
          if (!empty($this->pager->options['offset'])) {
            $this->pager->total_items -= $this->pager->options['offset'];
          }
        }
        $this->pager->update_page_info();
      }

      // Deal with offset & limit.
      $offset = !empty($this->offset) ? intval($this->offset) : 0;
      $limit = !empty($this->limit) ? intval($this->limit) : 0;
      $rows = $limit ? array_slice($rows, $offset, $limit) : array_slice($rows, $offset);

      $result = array();
      foreach ($rows as $row) {
        $new_row = new stdClass();
        $new_row = $this->parse_row(NULL, $row, $row);
        $result[] = (object) $new_row;
      }

      if (!empty($this->orderby)) {
        // Array reverse, because the most specific are first.
        foreach (array_reverse($this->orderby) as $orderby) {
          $orderby->sort($result);
        }
      }
      $view->result = $result;
      $view->total_rows = count($result);

      $this->pager->post_execute($view->result);

      return TRUE;
    }
    catch (Exception $e) {
      $view->result = array();
      if (!empty($view->live_preview)) {
        drupal_set_message(time());
        drupal_set_message($e->getMessage(), 'error');
      }
      else {
        debug($e->getMessage(), 'Views Json Backend');
      }
    }
  }

  /**
   * Parse row.
   *
   * A recursive function to flatten the json object.
   * Example:
   * {person:{name:{first_name:"John", last_name:"Doe"}}}
   * becomes:
   * $row->person/name/first_name = "John",
   * $row->person/name/last_name = "Doe"
   */
  function parse_row($parent_key, $parent_row, &$row) {
    $props = get_object_vars($parent_row);

    foreach ($props as $key => $value) {
      if (is_object($value)) {
        unset($row->$key);
        $this->parse_row(
          is_null($parent_key) ? $key : $parent_key . '/' . $key,
          $value,
          $row
        );
      }
      else {
        if ($parent_key) {
          $new_key = $parent_key . '/' . $key;
          $row->$new_key = $value;
        }
        else {
          $row->$key = $value;
        }
      }
    }

    return $row;
  }

  /**
   * Add signature.
   */
  function add_signature(&$view) {
  }

  /**
   * Option definition.
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['json_file'] = array('default' => '');
    $options['row_apath'] = array('default' => '');
    $options['total_items_apath'] = array('default' => '');
    $options['enable_pagination_query_parameters'] = array('default' => FALSE);
    $options['pagination_offset_query_parameter'] = array('default' => 'offset');
    $options['pagination_limit_query_parameter'] = array('default' => 'limit');
    $options['show_errors'] = array('default' => TRUE);

    $options['ssl_verify_peer'] = array('default' => FALSE, 'bool' => TRUE);
    $options['ssl_allow_self_signed'] = array('default' => FALSE);
    $options['ssl_cafile'] = array('default' => NULL);
    $options['ssl_capath'] = array('default' => NULL);
    $options['ssl_local_cert'] = array('default' => NULL);
    $options['ssl_passphrase'] = array('default' => NULL);
    $options['ssl_CN_match'] = array('default' => NULL);
    $options['ssl_verify_depth'] = array('default' => NULL);
    if (version_compare(PHP_VERSION, '5.0.0') >= 0) {
      $options['ssl_ciphers'] = array('default' => 'DEFAULT');
    }
    if (version_compare(PHP_VERSION, '5.3.2') >= 0) {
      $options['ssl_SNI_enabled'] = array('default' => NULL);
      $options['ssl_SNI_server_name'] = array('default' => NULL);
    }
    if (version_compare(PHP_VERSION, '5.4.13') >= 0) {
      $options['disable_compression'] = array('default' => FALSE);
    }
    if (version_compare(PHP_VERSION, '5.6.0') >= 0) {
      $options['ssl_peer_fingerprint'] = array('default' => NULL);
    }
    return $options;
  }

  /**
   * Options form.
   */
  function options_form(&$form, &$form_state) {
    $form['json_file'] = array(
      '#type' => 'textfield',
      '#title' => t('Json File'),
      '#default_value' => $this->options['json_file'],
      '#description' => t("The URL or path to the Json file."),
      '#maxlength' => 1024,
    );
    $form['row_apath'] = array(
      '#type' => 'textfield',
      '#title' => t('Root path'),
      '#default_value' => $this->options['row_apath'],
      '#description' => t("Root path to records.<br />Root path is just a simple array item find method. Ex:<br /><pre>array('data' => \n\tarray('records' => \n\t\tarray(\n\t\t\tarray('name' => 'yarco', 'sex' => 'male'),\n\t\t\tarray('name' => 'someone', 'sex' => 'male')\n\t\t)\n\t)\n)</pre><br />You want 'records', so root path could be set to 'data/records'. <br />Notice: prefix '/' or postfix '/' will be trimed, so never mind you add it or not."),
      '#required' => TRUE,
    );
    $form['total_items_apath'] = array(
      '#type' => 'textfield',
      '#title' => t('Records count path'),
      '#default_value' => $this->options['total_items_apath'],
      '#description' => t("Path to records count."),
      '#required' => FALSE,
    );
    $form['enable_pagination_query_parameters'] = array(
      '#type' => 'checkbox',
      '#title' => t('Enable pagination query parameters '),
      '#default_value' => $this->options['enable_pagination_query_parameters'],
    );
    $form['pagination_offset_query_parameter'] = array(
      '#type' => 'textfield',
      '#title' => t('Offset parameter name '),
      '#default_value' => $this->options['pagination_offset_query_parameter'],
      '#description' => t('The name of the pagination offset parameter'),
      '#states' => array(
        'visible' => array(':input[name="query[options][enable_pagination_query_parameters]"]' => array('checked' => TRUE)),
      )
    );
    $form['pagination_limit_query_parameter'] = array(
      '#type' => 'textfield',
      '#title' => t('Limit parameter name '),
      '#default_value' => $this->options['pagination_limit_query_parameter'],
      '#description' => t('The name of the pagination limit parameter'),
      '#states' => array(
        'visible' => array(':input[name="query[options][enable_pagination_query_parameters]"]' => array('checked' => TRUE)),
      )
    );
    $form['show_errors'] = array(
      '#type' => 'checkbox',
      '#title' => t('Show Json errors'),
      '#default_value' => $this->options['show_errors'],
      '#description' => t('If there were any errors during Json parsing, display them. It is recommended to leave this on during development.'),
      '#required' => FALSE,
    );
    $form['ssl'] = array(
      '#type' => 'fieldset',
      '#title' => t('SSL Options'),
      '#description' => t('Options used for HTTP requests when the Json File is an HTTPS URL.'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#parents' => array('query', 'options'),
    );
    $form['ssl']['ssl_verify_peer'] = array(
      '#type' => 'checkbox',
      '#title' => t('Require verification of SSL certificate used. '),
      '#default_value' => $this->options['ssl_verify_peer'],
      '#required' => FALSE,
    );
    $form['ssl']['ssl_allow_self_signed'] = array(
      '#type' => 'checkbox',
      '#title' => t('Allow self-signed certificates.'),
      '#default_value' => $this->options['ssl_allow_self_signed'],
      '#required' => FALSE,
      '#states' => array(
        'visible' => array(':input[name="query[options][ssl_verify_peer]"]' => array('checked' => TRUE)),
      )
    );
    $form['ssl']['ssl_cafile'] = array(
      '#type' => 'textfield',
      '#title' => t('Certificate Authority file'),
      '#description' => t('Location of Certificate Authority file on local filesystem which should be used to authenticate the identity of the remote peer.'),
      '#default_value' => $this->options['ssl_cafile'],
      '#required' => FALSE,
      '#states' => array(
        'visible' => array(':input[name="query[options][ssl_verify_peer]"]' => array('checked' => TRUE)),
      )
    );
    $form['ssl']['ssl_capath'] = array(
      '#type' => 'textfield',
      '#title' => t('Certificate Authority path'),
      '#description' => t('If cafile is not specified or if the certificate is not found there, the directory pointed to by capath is searched for a suitable certificate. capath must be a correctly hashed certificate directory.'),
      '#default_value' => $this->options['ssl_capath'],
      '#required' => FALSE,
      '#states' => array(
        'visible' => array(':input[name="query[options][ssl_verify_peer]"]' => array('checked' => TRUE)),
      )
    );
    $form['ssl']['ssl_local_cert'] = array(
      '#type' => 'textfield',
      '#title' => t('Local certificate'),
      '#description' => t('Path to local certificate file on filesystem. It must be a PEM encoded file which contains your certificate and private key. It can optionally contain the certificate chain of issuers.'),
      '#default_value' => $this->options['ssl_local_cert'],
      '#required' => FALSE,
    );
    $form['ssl']['ssl_passphrase'] = array(
      '#type' => 'textfield',
      '#title' => t('Passphrase'),
      '#description' => t('Passphrase with which your local certificate file was encoded.'),
      '#default_value' => $this->options['ssl_passphrase'],
      '#required' => FALSE,
      '#states' => array(
        'visible' => array(':input[name="query[options][ssl_local_cert]"]' => array('filled' => TRUE)),
      )
    );
    $form['ssl']['ssl_CN_match'] = array(
      '#type' => 'textfield',
      '#title' => t('Common Name'),
      '#description' => t('Common Name we are expecting. PHP will perform limited wildcard matching. If the Common Name does not match this, the connection attempt will fail.'),
      '#default_value' => $this->options['ssl_CN_match'],
      '#required' => FALSE,
    );
    $form['ssl']['ssl_verify_depth'] = array(
      '#type' => 'textfield',
      '#title' => t('Maximum certificate chain depth'),
      '#description' => t('Abort if the certificate chain is too deep. Leave empty to disable verification.'),
      '#default_value' => $this->options['ssl_verify_depth'],
      '#required' => FALSE,
    );
    if (version_compare(PHP_VERSION, '5.0.0') >= 0) {
      $form['ssl']['ssl_ciphers'] = array(
        '#type' => 'textfield',
        '#title' => t('Ciphers'),
        '#description' => t('Sets the list of available ciphers. The format of the string is described in <a href="@url">ciphers(1)</a>.', array('@url' => 'http://www.openssl.org/docs/apps/ciphers.html#CIPHER_LIST_FORMAT')),
        '#default_value' => $this->options['ssl_ciphers'],
        '#required' => TRUE,
      );
    }
    if (version_compare(PHP_VERSION, '5.3.2') >= 0) {
      $form['ssl']['ssl_SNI_enabled'] = array(
        '#type' => 'checkbox',
        '#title' => t('Enable SNI'),
        '#description' => t('Enabling SNI allows multiple certificates on the same IP address.'),
        '#default_value' => $this->options['ssl_SNI_enabled'],
        '#required' => FALSE,
      );
      $form['ssl']['ssl_SNI_server_name'] = array(
        '#type' => 'textfield',
        '#title' => t('SNI Server Name'),
        '#description' => t('If set, then this value will be used as server name for server name indication. If this value is not set, then the server name is guessed based on the hostname used when opening the stream.'),
        '#default_value' => $this->options['ssl_SNI_server_name'],
        '#required' => FALSE,
        '#states' => array(
          'visible' => array(':input[name="query[options][ssl_SNI_enabled]"]' => array('checked' => TRUE)),
        )
      );
    }
    if (version_compare(PHP_VERSION, '5.4.13') >= 0) {
      $form['ssl']['ssl_disable_compression'] = array(
        '#type' => 'checkbox',
        '#title' => t('Disable TLS compression. This can help mitigate the CRIME attack vector.'),
        '#default_value' => $this->options['ssl_disable_compression'],
        '#required' => FALSE,
      );
    }
    if (version_compare(PHP_VERSION, '5.6.0') >= 0) {
      $form['ssl']['ssl_peer_fingerprint'] = array(
        '#type' => 'textfield',
        '#title' => t('Peer Fingerprint'),
        '#description' => t("Aborts when the remote certificate digest doesn't match the specified hash. Leave empty to disable verification. The length will determine which hashing algorithm is applied, either 'md5' (32) or 'sha1' (40)"),
        '#default_value' => $this->options['ssl_peer_fingerprint'],
        '#required' => FALSE,
      );
    }
  }

  /**
   * Add field.
   */
  function add_field($table, $field, $alias = '', $params = array()) {
    $alias = $field;

    // Add field info array.
    if (empty($this->fields[$field])) {
      $this->fields[$field] = array(
        'field' => $field,
        'table' => $table,
        'alias' => $alias,
      ) + $params;
    }

    return $field;
  }

  /**
   * Add Order By.
   */
  function add_orderby($orderby) {
    $this->orderby[] = $orderby;
  }

  /**
   * Add Filter.
   */
  function add_filter($filter) {
    $this->filter[] = $filter;
  }

  /**
   * Return info to base the uniqueness of the result on.
   *
   * @return array
   *   Array with query unique data.
   */
  function get_cache_info() {
    return array(
      'json_file' => $this->options['json_file'],
      'row_apath' => $this->options['row_apath'],
    );
  }
}
