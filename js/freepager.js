(function ($, Drupal, drupalSettings) {
  Drupal.behaviors.freepager = {
    attach: function (context) {
      var $ = jQuery;

      function leftArrowPressed() {
        if ($(".freepager-previous", context).length) {
          window.location = $(".freepager-previous > a", context).attr('href');
        }
      }

      function rightArrowPressed() {
        if ($(".freepager-next", context).length) {
          window.location = $(".freepager-next > a", context).attr('href');
        }
      }

      $(document).keydown(function (event) {
        switch (event.which) {
          case 37:
            leftArrowPressed();
            break;
          case 39:
            rightArrowPressed();
            break;
        }
      });

      $(document).swipeleft(function () {
        if (/Android|webOS|iPhone|iPad|iPod|BlackBerry/i.test(navigator.userAgent) && $(".freepager-previous", context).length) {
          window.location = $(".freepager-previous > a", context).attr('href');
        }
      });

      $(document).swiperight(function () {
        if (/Android|webOS|iPhone|iPad|iPod|BlackBerry/i.test(navigator.userAgent) && $(".freepager-next", context).length) {
          window.location = $(".freepager-next > a", context).attr('href');
        }
      });
    }
  }
})(jQuery, Drupal, drupalSettings);
