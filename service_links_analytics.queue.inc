<?php

/**
 * Service Links Analytics Queue
 *
 * Class uses data table as queue table.
 *
 * @see SystemQueue
 */
class ServiceLinksAnalyticsQueue implements DrupalReliableQueueInterface {
  /**
   * The name of the queue this instance is working with.
   *
   * @var string
   */
  protected $name;

  protected $expire;

  public function __construct($name) {
    $this->name = $name;
    $this->expire = variable_get('service_links_analytics_expire', 3600);
  }

  public function createItem($data) {
    $row = (object) $data;
    return service_links_analytics_save($row);
  }

  public function numberOfItems() {
    return db_query('SELECT COUNT(*) FROM {service_links_analytics} WHERE updated = 0 OR updated < :threshold', array(':threshold' => time() - $this->expire))->fetchField();
  }

  public function claimItem($lease_time = 30) {
    // Claim an item by updating its expire fields.
    while (TRUE) {
      $item = db_query_range('SELECT entity_type, entity_id, service, metric FROM {service_links_analytics} WHERE expire = 0 AND (updated = 0 OR updated < :threshold) ORDER BY updated ASC', 0, 1, array(':threshold' => time() - $this->expire))->fetchObject();
      $item->data = clone $item;
      if ($item->data) {
        // Try to update the item.
        $update = db_update('service_links_analytics')
          ->fields(array(
            'expire' => time() + $lease_time,
          ))
          ->condition('entity_type', $item->data->entity_type)
          ->condition('entity_id', $item->data->entity_id)
          ->condition('service', $item->data->service)
          ->condition('metric', $item->data->metric)
          ->condition('expire', 0);
        // If there are affected rows, this update succeeded.
        if ($update->execute()) {
          return $item;
        }
      }
      else {
        // No items currently available to claim.
        return FALSE;
      }
    }
  }

  public function releaseItem($item) {
    return db_update('service_links_analytics')
      ->fields(array(
        'expire' => 0,
      ))
      ->condition('entity_type', $item->data->entity_type)
      ->condition('entity_id', $item->data->entity_id)
      ->condition('service', $item->data->service)
      ->condition('metric', $item->data->metric)
      ->execute();
  }

  public function deleteItem($item) {
    return db_update('service_links_analytics')
      ->fields(array(
        'updated' => time(),
        'expire' => 0,
      ))
      ->condition('entity_type', $item->data->entity_type)
      ->condition('entity_id', $item->data->entity_id)
      ->condition('service', $item->data->service)
      ->condition('metric', $item->data->metric)
      ->execute();
  }

  public function createQueue() {
    // Queue is the data table.
  }

  public function deleteQueue() {
    // Never drop the data table.
  }
}
