<div class="pane-user-login">
<img src="/sites/dashboard7.dd/files/logo.png" width="250px"  border="0" alt=""> 

<p><?php // print render($intro_text); ?></p>
<div class="user-login-form-wrapper">



<form class="user-login" action="/user/recover" method="post" id="user-pass" accept-charset="UTF-8"><div>

<div class="form-item form-type-textfield form-item-name">
<label for="edit-name">Username or E-mail Address <span class="form-required" title="This field is required.">*</span></label>

<input type="text" id="edit-name" name="name" value=""  maxlength="254" class="form-text required" />
</div>

<input type="hidden" name="form_build_id" value="<?php print_r($form['form_build_id']['#value']); ?>" />
<input type="hidden" name="form_id" value="user_pass" />

<div class="form-actions form-wrapper" id="edit-actions"><input type="submit" id="edit-submit" name="op" value="Submit" class="form-submit" /></div></div>

</div>
</div>

</form>


