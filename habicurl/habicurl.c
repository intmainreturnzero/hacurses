#include <curl/curl.h>

#include "habicurl.h"

void habicurl_init()
{
    curl_global_init(CURL_GLOBAL_SSL);
}
