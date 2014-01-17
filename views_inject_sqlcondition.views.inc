<?php
/**
 * @file
 * Implements the display extender to add additional setting to views displays.
 */

/**
 * Implements hook_views_plugins().
 */
function views_inject_sqlcondition_views_plugins() {
  $path = drupal_get_path('module', 'views_custom_conditions');
  $plugins = array();
  $plugins['display_extender']['views_inject_sqlcondition'] = array(
    'title' => t('Extender textarea'),
    'help' => t('Add textarea.'),
    'path' => $path,
    'handler' => 'views_inject_sqlcondition_plugin_display_extender_code',
  );
  return $plugins;
}

/**
 * Implements hook_views_query_alter().
 */
function views_inject_sqlcondition_views_query_alter(&$view, &$query) {
  if (variable_get('views_inject_sqlcondition_' . $view->name.'_'.$view->current_display)) {
    $query_snippet = variable_get('views_inject_sqlcondition_' . $view->name.'_'.$view->current_display);
    $view->query->add_where_expression(0, $query_snippet);
  }
  return $query;
}
