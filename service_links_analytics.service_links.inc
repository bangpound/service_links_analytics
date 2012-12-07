<?php

function service_links_analytics_service_links_alter(&$links) {

  // From http://sharedcount.com/documentation.php
  $services = array(
    'facebook' => 'http://api.ak.facebook.com/restserver.php?v=1.0&method=links.getStats&urls=<encoded-url>&format=json',
    'twitter' => 'http://urls.api.twitter.com/1/urls/count.json?url=<encoded-url>',
    'reddit' => 'http://www.reddit.com/api/info.json?url=<encoded-url>',
    'linkedin' => 'http://www.linkedin.com/countserv/count/share?url=<encoded-url>&format=json',
    'delicious' => 'http://feeds.delicious.com/v2/json/urlinfo/data?url=<encoded-url>',
    'stumbleupon' => 'http://www.stumbleupon.com/services/1.01/badge.getinfo?url=<encoded-url>',
    'pinterest' => 'http://api.pinterest.com/v1/urls/count.json?url=<encoded-url>',
  );

  foreach ($services as $name => $url) {
    $links[$name]['analytics'] = $url;
  }

  $links['google_plus_one']['analytics_callback'] = 'service_links_analytics_google_plus_one_count';
}
