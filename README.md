# Status Report Drupal module
## Drupal module to provide statuses for integration services that can be intermittent and unstable.

[![Circle CI](https://circleci.com/gh/integratedexperts/status_report.svg?style=shield)](https://circleci.com/gh/alexdesignworks/status_report)

![sacreenshot](https://user-images.githubusercontent.com/378794/39668688-daf598bc-5117-11e8-9d15-5459278d164e.png)

## Why? 
If your module provides a 3rd party integration and you want to know that connection is configured correctly, this module allows to see all the response information in within a single page.

You may also implement status check for any other Drupal module that does not have such information page.

## Features
- Single page for all status checks.
- `<iframe>`-based status checks (useful for SSO with redirects).

## Getting started
1. Implement `hook_status_report_handlers()` to specify your status class.
2. Extend `StatusReport` class with your 3rd party endpoint request methods.
3. Go to `/admin/reports/integration-status-report` to check the status.

Refer to [status_report.api.php](status_report.api.php) for implementation example.
