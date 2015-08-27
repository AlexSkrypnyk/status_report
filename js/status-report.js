/**
 * @file
 * User status table JavaScript response handlers.
 */

/*global jQuery, window, Drupal*/
(function($) {
  "use strict";
  /**
   * Helper functions for User Status.
   */
  Drupal.StatusReport = Drupal.StatusReport || {
    /**
     * Update the status table with a status response.
     *
     * @param passed boolean
     *   Whether or not the status is a pass or fail.
     * @param className string
     *   The name of the PHP class the status response belongs to.
     * @param message string
     *   The messages returned by the status response class callback.
     * @param time number
     *   The amount of milliseconds it took to complete the callback.
     */
    statusReceived: function(passed, className, message, time) {
      var $statusRow = $('[data-status-result="' + className + '"]'),
          $statusDebug = $('[data-debug-result="' + className + '"]'),
          responseText = '';

      $statusRow.addClass('status-report-complete');

      if (time < 10000 && passed) {
        $statusRow.removeClass('warning').addClass('ok');
        $statusDebug.removeClass('open');
        responseText = 'OK';
      }
      else if (!passed) {
        $statusRow.removeClass('warning').addClass('error');
        responseText = 'FAIL';
        $statusRow.addClass('open');
        $statusDebug.addClass('open');
      }

      responseText += ' (' + time + 'ms)';

      $statusRow.find('.status-report-response').html(responseText);
      $statusRow.find('.status-report-message').append(message);
      $statusRow.find('.ajax-progress').remove();
    }
  };

  /**
   * Respond to postMessages on the page.
   *
   * Only fire statusReceived if the message is an object and has the type
   * 'bsUserStatusHandler'.
   */
  window.addEventListener('message', function(e) {
    if (e.data.type !== null && e.data.type === 'statusReportHandler') {
      Drupal.StatusReport.statusReceived(e.data.success, e.data.class, e.data.message, e.data.time);
    }
  }, false);

  /**
   * User status behavior for opening and closing status messages.
   */
  Drupal.behaviors.StatusReport = {
    attach: function(context, settings) {
      $('tr', context).click(function() {
        $(this).toggleClass('open');
      });
    }
  };
}(jQuery));
