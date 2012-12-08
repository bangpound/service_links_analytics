<?php

/**
 * Default queue implementation.
 */
class ServiceLinksAnalyticsQueue implements DrupalReliableQueueInterface {
  /**
   * The name of the queue this instance is working with.
   *
   * @var string
   */
  protected $name;

  public function __construct($name) {
    $this->name = $name;
  }

  public function createItem($data) {
    $row = (object) $data;
    return service_links_analytics_save($row);
  }

  public function numberOfItems() {
    return db_query('SELECT COUNT(*) FROM {service_links_analytics} WHERE updated = 0 OR updated < :threshold', array(':threshold' => REQUEST_TIME - 3600))->fetchField();
  }

  public function claimItem($lease_time = 30) {
    // Claim an item by updating its expire fields. If claim is not successful
    // another thread may have claimed the item in the meantime. Therefore loop
    // until an item is successfully claimed or we are reasonably sure there
    // are no unclaimed items left.
    while (TRUE) {
      $item = new stdClass();
      $item->data = db_query_range('SELECT entity_type, entity_id FROM {service_links_analytics} q WHERE expire = 0 AND (updated = 0 OR updated < :threshold) ORDER BY updated ASC', 0, 1, array(':threshold' => REQUEST_TIME - 3600))->fetchObject();
      if ($item) {
        // Try to update the item. Only one thread can succeed in UPDATEing the
        // same row. We cannot rely on REQUEST_TIME because items might be
        // claimed by a single consumer which runs longer than 1 second. If we
        // continue to use REQUEST_TIME instead of the current time(), we steal
        // time from the lease, and will tend to reset items before the lease
        // should really expire.
        $update = db_update('service_links_analytics')
          ->fields(array(
            'expire' => time() + $lease_time,
          ))
          ->condition('entity_type', $item->data->entity_type)
          ->condition('entity_id', $item->data->entity_id)
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
      ->execute();
  }

  public function createQueue() {
    // Queue is the data table.
  }

  public function deleteQueue() {
    // Never drop the data table.
  }
}
