<?php

/**
 * @file
 * Bulk export of views_default objects generated by Bulk export module.
 */

/**
 * Implements hook_views_default_views().
 */
function service_links_analytics_views_default_views() {
  $views = array();

  $view = new view();
  $view->name = 'metrics';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'service_links_analytics';
  $view->human_name = 'Metrics';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Metrics';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'service' => 'service',
    'metric' => 'metric',
    'value' => 'value',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'service' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'metric' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'value' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Field: Service links analytics: Service */
  $handler->display->display_options['fields']['service']['id'] = 'service';
  $handler->display->display_options['fields']['service']['table'] = 'service_links_analytics';
  $handler->display->display_options['fields']['service']['field'] = 'service';
  /* Field: Service links analytics: Metric */
  $handler->display->display_options['fields']['metric']['id'] = 'metric';
  $handler->display->display_options['fields']['metric']['table'] = 'service_links_analytics';
  $handler->display->display_options['fields']['metric']['field'] = 'metric';
  /* Field: Service links analytics: Value */
  $handler->display->display_options['fields']['value']['id'] = 'value';
  $handler->display->display_options['fields']['value']['table'] = 'service_links_analytics';
  $handler->display->display_options['fields']['value']['field'] = 'value';
  /* Contextual filter: Service links analytics: entity_id */
  $handler->display->display_options['arguments']['entity_id']['id'] = 'entity_id';
  $handler->display->display_options['arguments']['entity_id']['table'] = 'service_links_analytics';
  $handler->display->display_options['arguments']['entity_id']['field'] = 'entity_id';
  $handler->display->display_options['arguments']['entity_id']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['entity_id']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['entity_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['entity_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['entity_id']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Service links analytics: Entity type */
  $handler->display->display_options['filters']['entity_type']['id'] = 'entity_type';
  $handler->display->display_options['filters']['entity_type']['table'] = 'service_links_analytics';
  $handler->display->display_options['filters']['entity_type']['field'] = 'entity_type';
  $handler->display->display_options['filters']['entity_type']['value'] = 'node';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['path'] = 'node/%/metrics';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Metrics';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $translatables['metrics'] = array(
    t('Master'),
    t('Metrics'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Service'),
    t('Metric'),
    t('Value'),
    t('.'),
    t(','),
    t('All'),
    t('Page'),
  );
  $views['metrics'] = $view;

  return $views;
}
