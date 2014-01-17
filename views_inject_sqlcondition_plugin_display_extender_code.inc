<?php
/**
 * @file
 * Contains the class to extend views display plugins browse all link.
 */

/**
 * The plugin that added additional setting to views edit form.
 *
 * @ingroup views_display_plugins
 */
class views_inject_sqlcondition_plugin_display_extender_code extends views_plugin_display_extender {
  // Provide a form to edit options for this plugin.
  function options_definition() {
    $options['views_inject_sqlcondition'] = array('default' => '');
  }

  /**
   * Provide the form to set new option.
   */
  function options_form(&$form, &$form_state) {

    switch ($form_state['section']) {
      case 'views_inject_sqlcondition':
        $form['#title'] .= t('Setting');
        $form['views_inject_sqlcondition'] = array(
          '#type' => 'textarea',
          '#description' => t('Enter here your SQL condition code.'),
          '#default_value' => $this->display->get_option('views_inject_sqlcondition'),
        );
        break;
    }
  }

  /**
   * Inserts the code into the view display.
   */
  function options_submit(&$form, &$form_state) {

    // Not sure I like this being here, but it seems (?) like a logical place.
    $new_option  = $form_state['values']['views_inject_sqlcondition'];
    variable_set('views_inject_sqlcondition_' . $form_state['view']->name.'_'.$form_state['view']->current_display, $new_option);

    switch ($form_state['section']) {
      case 'views_inject_sqlcondition':
        $this->display->set_option('views_inject_sqlcondition', $new_option);
        $empty = trim($new_option);
        $empty = empty($empty);
      break;
    }
    foreach ($this->extender as $extender) {
      $extender->options_submit($form, $form_state);
    }
  }

  /**
   * Summarizes new option.
   *
   * Lists the fields as either 'Yes' if there is text or 'None' otherwise and
   * categorizes the fields under the 'Other' category.
   */
  function options_summary(&$categories, &$options) {

    $new_option = check_plain(trim($this->display->get_option('views_inject_sqlcondition')));

    if ($new_option) {
      $new_option = t('Set');
    }
    else {
      $new_option = t('Not Set');
    }
    $options['views_inject_sqlcondition'] = array(
      'category' => 'other',
      'title'    => t('Views Inject SQL Condition'),
      'value'    => $new_option,
      'desc'     => t('Add some option.'),
    );
  }
}
