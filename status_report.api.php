<?php
/**
 * @file
 * Api documentation for Status Report module.
 */

/**
 * Implement this hook to return status handler classes that should be executed.
 *
 * @return array
 *   A list of class names for status handlers.
 */
function hook_status_report_handlers() {
  return [
    'MyModuleExampleStatusReport',
  ];
}

/**
 * Status Report handler class.
 *
 * Include status handler classes within inc files inside a status directory
 * within the related module. Remember to also add your includes to the files[]
 * declaration in the module info page.
 */
class MyModuleExampleStatusReport extends StatusReport {

  /**
   * Define the properties of the status.
   *
   * Required for each status handler.
   *
   * @return array
   *   An array defining the status with the keys:
   *   - 'name' (string, required)
   *       The name of the status being checked.
   *   - 'description' (string, required)
   *       The description of the status being checked.
   *   - 'js' (string, optional)
   *       A javascript helper file to include on the status page.
   *   - 'secure_callback' (bool, optional - default: FALSE)
   *       Whether the status callback needs to be performed over https.
   *   - 'use_callback' (bool, optional - default: TRUE)
   *       Whether or not to use the standard iFrame callback method.
   *   - 'access' (bool, optional - default: TRUE)
   *       Whether the status check is available based on additional custom
   *       conditions such as environment or user permission.
   */
  public function info() {
    return [
      // Required parameters:
      'name' => t('Status name'),
      'description' => t('Status description'),
      // Optional parameters:
      'js' => drupal_get_path('module', 'example_module') . '/status/example-module-status.js',
      'secure_callback' => FALSE,
      'use_callback' => FALSE,
      'access' => TRUE,
    ];
  }

  /**
   * The callback for running checks and returning responses.
   *
   * Required for each status handler unless 'use_callback' is set to FALSE in
   * the info declaration.
   *
   * @return array
   *   - 'success' (bool, required)
   *       Whether or not the status check was a success or failure.
   *   - 'messages' (array, required)
   *       A list of string messages to be added to the response information
   *       for the test.
   */
  public function callback() {
    // Perform a request on an example url.
    $url = 'http://exampleurl.com';
    $response = drupal_http_request($url);

    // Check for a 200 response and the word 'text' in the response.
    if ($response->code == '200' && strpos($response->data, 'text') !== FALSE) {
      $success = TRUE;
      $messages[] = t('@url retrieved successfully.', [
        '@url' => $url,
      ]);
    }
    else {
      $success = FALSE;
      $messages[] = t('@url not retrieved successfully.', [
        '@url' => $url,
      ]);
    }

    return [
      'success' => $success,
      'messages' => $messages,
    ];
  }

  /**
   * Add any extra markup or javascript to the footer of the status table.
   *
   * Optional, not required for most status checks.
   *
   * @return string
   *   Markup to be placed in the footer of the table.
   */
  public function statusPage() {
    return '<div class="extra-status-markup">FOO</div>';
  }

}
