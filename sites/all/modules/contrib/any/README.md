# Any Dependency

This module does nothing on its own other than provide an API that
allows modules a way to specify any dependency, based on a list.

This is, in part, due to the vast Drupal ecosystem where there are
tons of "similar" projects that do almost the same thing but just
"slightly" different. To compensate for a site that may use one
variety of "popular" module over another, this allows a module
to support multiple projects.

This modules was originally created for the [Service Container](https://www.drupal.org/project/service_container)
module and inspired from [Allow usage of alternative autoloaders](https://www.drupal.org/project/service_container/issues/2608500).

### Setup

Setup is relatively easy. Just add the following to your module's `.info` file.

```
dependencies[] = any
any[] = some_contrib_module (>= 7.x-1.3)
any[] = another_similar_contrib_module (>= 7.x-5.0)
any[] = yet_one_more_contrib_module
```

**Note:** the order of these dependencies is important. The first
one to be found will be used.

Once a valid dependency has been found, this module will automatically
add it as a hard dependency in your module's `info` definition.

Once that is done, you will also need to add the following to your
module's `.install` file to ensure that it isn't installable until at
least one of these modules is available:

```php
<?php
/**
 * Implements hook_requirements().
 */
function MY_MODULE_requirements($phase) {
  // Attempt to load the "any" dependencies module.
  if (!module_exists('any')) {
    module_enable(['any']);
  }

  // If "any" still doesn't exist then inform the user.
  if (!module_exists('any')) {
    $t = get_t();
    $requirements["MY_MODULE-missing-any"] = [
      'title' => $t('Missing "any" dependency'),
      'description' => $t('The module "MY_MODULE" requires the !url project. Please download and install it first.', [
        '!url' => 'https://www.drupal.org/project/any',
      ]),
      'severity' => REQUIREMENT_ERROR,
    ];
    return $requirements;
  }

  // Load the "any" module and let it perform requirement checks.
  drupal_load('module', 'any');
  return any_check_install_requirements($phase, 'MY_MODULE');
}
```

### Advanced Grouping

For complex dependencies, an optional "group" may be specified.
If no group has been specified, it will default to `dependencies`:

```
dependencies[] = any
any[group1] = some_contrib_module (>= 7.x-2.0)
any[group1] = another_similar_contrib_module (>= 7.x-2.0)
any[group2] = another_similar_contrib_module
any[group2] = yet_one_more_contrib_module
```

**Note:*** this functionality is still a work-in-progress. Its
functionality/features may fluctuate or radically change in future
releases.

### Drush

There is minimal support for Drush to help install dependencies.

**Note:** this functionality is still a work-in-progress. Its
functionality/features may fluctuate or radically change in future
releases.
