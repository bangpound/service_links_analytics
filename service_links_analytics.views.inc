<?php

function service_links_analytics_views_data() {
  $data = array(
    'service_links_analytics' => array(
      'table' => array(
        'group' => 'Service links analytics',
        'base' => array(
          'field' => 'entity_type',
          'title' => 'Service links analytics',
          'help' => 'Data table',
          'weight' => 10,
        ),
      ),
      'entity_type' => array(
        'title' => 'Entity type',
        'help' => 'Entity type',
        'field' => array(
          'handler' => 'views_handler_field',
          'help' => 'Entity type',
          'click sortable' => TRUE,
        ),
        'filter' => array(
          'handler' => 'views_handler_filter_string',
          'allow empty' => TRUE,
          'help' => 'Filter on <em class="placeholder">Entity type</em>',
        ),
        'argument' => array(
          'handler' => 'views_handler_argument_string',
          'help' => 'Entity type',
        ),
        'sort' => array(
          'handler' => 'views_handler_sort',
          'help' => 'Sort by <em class="placeholder">Entity type</em>',
        ),
      ),
      'entity_id' => array(
        'title' => 'entity_id',
        'help' => 'entity_id',
        'field' => array(
          'handler' => 'views_handler_field_numeric',
          'help' => 'entity_id',
          'click sortable' => TRUE,
        ),
        'filter' => array(
          'handler' => 'views_handler_filter_numeric',
          'allow empty' => TRUE,
          'help' => 'Filter on <em class="placeholder">entity_id</em>',
        ),
        'argument' => array(
          'handler' => 'views_handler_argument_numeric',
          'help' => 'entity_id',
        ),
        'sort' => array(
          'handler' => 'views_handler_sort',
          'help' => 'Sort by <em class="placeholder">entity_id</em>',
        ),
      ),
      'service' => array(
        'title' => 'Service',
        'help' => 'Service',
        'field' => array(
          'handler' => 'views_handler_field',
          'help' => 'Service',
          'click sortable' => TRUE,
        ),
        'filter' => array(
          'handler' => 'views_handler_filter_string',
          'allow empty' => TRUE,
          'help' => 'Filter on <em class="placeholder">Service</em>',
        ),
        'argument' => array(
          'handler' => 'views_handler_argument_string',
          'help' => 'Service',
        ),
        'sort' => array(
          'handler' => 'views_handler_sort',
          'help' => 'Sort by <em class="placeholder">Service</em>',
        ),
      ),
      'metric' => array(
        'title' => 'Metric',
        'help' => 'Metric',
        'field' => array(
          'handler' => 'views_handler_field',
          'help' => 'Metric',
          'click sortable' => TRUE,
        ),
        'filter' => array(
          'handler' => 'views_handler_filter_string',
          'allow empty' => TRUE,
          'help' => 'Filter on <em class="placeholder">Metric</em>',
        ),
        'argument' => array(
          'handler' => 'views_handler_argument_string',
          'help' => 'Metric',
        ),
        'sort' => array(
          'handler' => 'views_handler_sort',
          'help' => 'Sort by <em class="placeholder">Metric</em>',
        ),
      ),
      'value' => array(
        'title' => 'Value',
        'help' => 'Value',
        'field' => array(
          'handler' => 'views_handler_field_numeric',
          'help' => 'Value',
          'click sortable' => TRUE,
        ),
        'filter' => array(
          'handler' => 'views_handler_filter_numeric',
          'allow empty' => TRUE,
          'help' => 'Filter on <em class="placeholder">Value</em>',
        ),
        'argument' => array(
          'handler' => 'views_handler_argument_numeric',
          'help' => 'Value',
        ),
        'sort' => array(
          'handler' => 'views_handler_sort',
          'help' => 'Sort by <em class="placeholder">Value</em>',
        ),
      ),
      'refresh' => array(
        'title' => 'Refresh',
        'help' => 'Refresh',
        'field' => array(
          'handler' => 'views_handler_field_date',
          'help' => 'Refresh',
          'click sortable' => TRUE,
        ),
        'filter' => array(
          'handler' => 'views_handler_filter_date',
          'allow empty' => TRUE,
          'help' => 'Filter on <em class="placeholder">Refresh</em>',
        ),
        'argument' => array(
          'handler' => 'views_handler_argument_date',
          'help' => 'Refresh',
        ),
        'sort' => array(
          'handler' => 'views_handler_sort_date',
          'help' => 'Sort by <em class="placeholder">Refresh</em>',
        ),
      ),
      'expire' => array(
        'title' => 'Expire',
        'help' => 'Expire',
        'field' => array(
          'handler' => 'views_handler_field_date',
          'help' => 'Expire',
          'click sortable' => TRUE,
        ),
        'filter' => array(
          'handler' => 'views_handler_filter_date',
          'allow empty' => TRUE,
          'help' => 'Filter on <em class="placeholder">Expire</em>',
        ),
        'argument' => array(
          'handler' => 'views_handler_argument_date',
          'help' => 'Expire',
        ),
        'sort' => array(
          'handler' => 'views_handler_sort_date',
          'help' => 'Sort by <em class="placeholder">Expire</em>',
        ),
      ),
    ),
  );

  $groups = array();
  foreach (variable_get('service_links_analytics_entity_types', array('node')) as $type) {
    $entity_info = entity_get_info($type);
    $groups[$type] = $entity_info['label'];

    // Override Node to Content.
    if ($groups[$type] == t('Node')) {
      $groups[$type] = t('Content');
    }

    $data['service_links_analytics']['table']['join'][$entity_info['base table']] = array(
      'left_field' => $entity_info['entity keys']['id'],
      'field' => 'entity_id',
      'extra' => array(
        array('field' => 'entity_type', 'value' => $type),
      ),
    );

    $data['service_links_analytics']['entity_id_'. $entity_info['entity keys']['id']] = array(
      'title' => $entity_info['label'],
      'help' => 'Help text.',
      'real field' => 'entity_id',
      'relationship' => array(
        'base' => $entity_info['base table'],
        'base field' => $entity_info['entity keys']['id'],
        'extra' => array(
          array(
            'table' => 'service_links_analytics',
            'field' => 'entity_type',
            'value' => $type,
          ),
        ),
      ),
    );
  }

  return $data;
}
