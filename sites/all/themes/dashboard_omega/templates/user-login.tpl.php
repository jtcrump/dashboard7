<div class="pane-user-login">
<img src="/sites/dashboard7.dd/files/logo.png" width="250px"  border="0" alt=""> 

<p><?php print render($intro_text); ?></p>
<div class="user-login-form-wrapper">
<form class="user-login" action="/user" method="post" id="user-login" accept-charset="UTF-8"><div>

  <div class="form-item form-type-textfield form-item-name">
  <label for="edit-name"><span class="form-required" title="This field is required.">*</span></label>
 <input type="text" id="edit-name" name="name" value=""  maxlength="60" class="form-text required" placeholder=" Email" />
<div class="description"></div>
</div>
<div class="form-item form-type-password form-item-pass">
  <label for="edit-pass"><span class="form-required" title="This field is required.">*</span></label>
 <input type="password" id="edit-pass" name="pass"  maxlength="128" class="form-text required" placeholder=" Password" />
<div class="description"></div>

<div class="reset"><a href="/user/recover">Forgot password?</a></div>

</div>
<input type="hidden" name="form_build_id" value="<?php print_r($form['form_build_id']['#value']); ?>" />
<input type="hidden" name="form_id" value="user_login" />
<div class="form-actions form-wrapper" id="edit-actions"><input type="submit" id="edit-submit" name="op" value="Sign In" class="form-submit" /></div>
</div>

</div></form>  
</div></div>