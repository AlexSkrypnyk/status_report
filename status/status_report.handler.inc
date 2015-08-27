<?php
/**
 * @file
 * StatusReport class for extension by status subclasses.
 */

abstract class StatusReport {
  // Name of the status handler, set by info().
  public $name;

  // Description of the status handler, set by info().
  public $description;

  // Javascript file for the status handler, set by info().
  public $js;

  // Whether or not to use the callback in the status handler, set by info().
  public $useCallback;

  // Whether the status callback needs to be performed over https.
  public $secureCallback;

  /**
   * Class constructor.
   *
   * Extract status meta information and fill the class variables.
   */
  public function __construct() {
    if ($info = $this->info()) {
      $this->name = $info['name'];
      $this->description = $info['description'];
      if (isset($info['js'])) {
        $this->js = $info['js'];
      }
      $this->useCallback = isset($info['use_callback']) ? $info['use_callback'] : TRUE;
      $this->secureCallback = isset($info['secure_callback']) ? $info['secure_callback'] : FALSE;
    }
  }

  /**
   * Retrieve a JavaScript parent post message script for a given status class.
   *
   * JavaScript is printed inside an iFrame that's loaded on the status page.
   * After the iFrame has loaded, the post message script is executed to the
   * parent window and the status is interpreted by the status table.
   *
   * @return string
   *   JavaScript markup that performs a postMessage to the parent window.
   */
  public function menuCallback() {
    // Log the time in which the menu callback php task begun.
    $start_time = round(microtime(TRUE) * 1000);

    // Perform the status handler's callback function.
    $results = $this->callback();

    // Log the amount of time it took for the callback function to complete.
    $results['time'] = round(microtime(TRUE) * 1000) - $start_time;

    // Get the class name for the current class.
    $results['class'] = get_class($this);

    // Add the type so that postMessages are distinguished.
    $results['type'] = 'statusReportHandler';

    // Format any messages as an unordered list.
    if (isset($results['messages'])) {
      $results['message'] = theme('item_list', array(
        'items' => $results['messages'],
        'title' => '',
        'type' => 'ul',
        'attributes' => array(),
      ));
    }
    else {
      $results['message'] = '';
    }

    // Encode the results as a json response and return in a postMessage.
    $encoded_js_result = drupal_json_encode($results);
    return '<script type="text/javascript">parent.postMessage(' . $encoded_js_result . ',"*");</script>';
  }

  /**
   * Check whether the status check should be available in this environment.
   *
   * @return bool
   *   Status check availability.
   */
  public function access() {
    $info = $this->info();
    if (isset($info['access']) && !$info['access']) {
      return FALSE;
    }
    else {
      return TRUE;
    }
  }

  /**
   * Info callback for injecting markup into status table suffix.
   *
   * @see status_report.api.php
   */
  public function info() {
    $no_info_message = t('Please specify an info hook for status %class.', array(
      '%class' => get_class($this),
    ));
    return array(
      'name' => $no_info_message,
      'description' => $no_info_message,
    );
  }

  /**
   * Status page callback for injecting markup into status table suffix.
   *
   * @see status_report.api.php
   */
  public function statusPage() {
  }

  /**
   * Callback handler for performing status operations and returning messages.
   *
   * @see status_report.api.php
   */
  public function callback() {
    return array(
      'success' => FALSE,
      'messages' => t('Please specify a callback for status %class or use the "no_callback" flag in status info.', array(
        '%class' => get_class($this),
      )),
    );
  }
}
