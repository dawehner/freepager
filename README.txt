This module allows you to use Views to create simple forward/next pagers. It
provides a new style, Pager, where you can set (a) the view field to use for
path, (b+c) the view fields to use for forward/next text, and (d) if you should
allow HTML in the link text – which is useful if you want to use images for
links.

When rendered, the view will check the URL fields against the current URL,
identify the active page and display previous/next links to the URLs above and
after.

Using this you could for example do the following:

  * Create a view of all users, sorted alphabetically, and display it as a block
    to allow browsing of users. (See screenshot above.) Or restrict it to users
    of a particular role, and you can browse editors on the site. Or whatever.
  * Create a view of all comments on the site, and you can browse
    forward/backward between comments. Or restrict the list to comments on the
    active node, and you can browse forward/backward between only these
    comments.
  * If you have seven administration pages that editors should visit often, you
    could even have Views listing these seven URLs and then have pagers on
    administration pages!

And more. As long as you can get a list of URLs into views, you can display it
as a pager. Easy as that!


It's the first time I've done a Views plugin, so I expect that there are things
that really could be better:

    * I failed calling the preprocess function for the template file I'm using,
      so a lot of logic goes into the rendering function in the Views plugin.
    * I would really like to move a lot of logic to where the view is being
      built rather than rendered – for example allowing the view to be really
      empty if there is no paging to display (even when the view has rows).

If you have skills in writing Views plugins I would be more than happy to hear
what mistakes I have made, and how it could be made better. :-)