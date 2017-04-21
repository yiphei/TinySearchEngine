
### Webpage fetching and parsing

We also looked at the `web.c` and `web.h` files that are provided in the [Lab 4]({{site.labs}}/Lab4.html) starter kit.  This module defines the `WebPage` type:

```c
// Structure to represent a web page, and its contents
typedef struct WebPage {
  char *url;                               // url of the page
  char *html;                              // html code of the page
  size_t html_len;                         // length of html code
  int depth;                               // depth of crawl
} WebPage;
```

This module provides the following functions:

 * **GetWebPage**: curl `page->url`, store into `page->html`.
	
```c
bool GetWebPage(WebPage *page);
```

 * **GetNextURL**: returns the next URL from `html[pos]` into `result`.

```c
int GetNextURL(char *html, int pos, char *base_url, char **result);
```

 * **NormalizeURL**: returns false if the URL can't be parsed or normalized; returns false if the url refers to a file unlikely to contain html; otherwise, modifies the URL into canonical form and returns true.

```c
bool NormalizeURL(char *url);
```

 * **IsInternalURL**: Returns true if the URL is valid and 'internal' to our domain.

```c
bool IsInternalURL(char *url);
```

Read the `web.h` file for full documentation of the interfaces.
