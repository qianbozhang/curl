#include <iostream>
#include <stdio.h>
#include <curl/curl.h>

//data header
/**
 * @breif: file header callback
 * 
 * @param[in] buffer: buffer points to the delivered[传递] data
 * @param[in] size: always 1
 * @param[in] nitems: the size of that data
 * @param[in] userp: user point
 * 
 * Note: libcurl 在收到标头数据后立即调用此函数
 * 
 * @return:
 * This callback function must return the number of bytes actually taken care of.
 * other: it will signal an error to the library
 */ 
static size_t header_callback(char *buffer, size_t size, size_t nitems, void *userp)
{
    printf("Reciver header %s \n", (char*)buffer);

    return size * nitems;
}


//data callback
/**
 * @brief: 一旦收到需要保存的数据，libcurl 就会调用此回调函数
 * 
 * @param[in] buffer: buffer points to the delivered[传递] data
 * @param[in] size: always 1
 * @param[in] nmemb: the size of that data
 * @param[in] userp: user point
 * 
 * Note:none
 * 
 * 
 * @return:
 *  callback should return the number of bytes actually taken care of.
 *  CURL_WRITEFUNC_PAUSE: will cause this transfer to become paused
 *  other: it will signal an error to the library
 */ 
static size_t chunk_callback(void *buffer, size_t size, size_t nmemb, void *userp)
{
    printf("Reciver chunk %lu \n", size * nmemb);
    FILE* fp = (FILE*)userp;

    fwrite(buffer, 1, size * nmemb, fp);

    return size * nmemb;
}

//progress
/**
 * @brief: progress callback
 * 
 * @param[in] clientp: 用户数据，透传
 * @param[in] dltotal: libcurl 期望在此传输中下载的总字节数
 * @param[in] dlnow: 到目前为止下载的字节数
 * @param[in] ultotal: libcurl 期望在此传输中上传的总字节数
 * @param[in] ulnow: 到目前为止上传的字节数
 * 
 * Note: CURLOPT_NOPROGRESS必须设置为0， 才能回调到progress_callback[该值默认为1，关闭了进度报告功能]
 * 
 * @return:
 * CURLE_OK: all is good
 * CURL_PROGRESSFUNC_CONTINUE: cause libcurl to continue executing the default progress function.
 * other non-zero value: cause libcurl to abort the transfer and return CURLE_ABORTED_BY_CALLBACK
 */
int progress_callback(void *clientp, double dltotal, double dlnow, double ultotal, double ulnow)
{
    static int num = 0;
    printf("progress: %f / %f \r", dlnow, dltotal);
    //call default fun
    // return CURL_PROGRESSFUNC_CONTINUE;
    //siganl abort
    if(num > 200)
        return !CURLE_OK;
    //all is good
    num ++;
    return CURLE_OK;
}


int main()
{
    CURLcode res;
    CURL *curl;
    FILE *fp;
    //global init
    curl_global_init(CURL_GLOBAL_DEFAULT);

    curl_version_info_data *ver = curl_version_info(CURLVERSION_NOW);
    printf("libcurl 版本 %u.%u.%u \n",
        (ver->version_num >> 16) & 0xff,
        (ver->version_num >> 8) & 0xff,
        ver->version_num & 0xff);


    //test uri:https://www.freedesktop.org/software/gstreamer-sdk/data/media/sintel_cropped_multilingual.webm
    curl = curl_easy_init();
    if(!curl)
        goto exit;

    printf("libcurl handle:%p \n", curl);
    
    //config
    curl_easy_setopt(curl, CURLOPT_URL, "https://www.freedesktop.org/software/gstreamer-sdk/data/media/sintel_cropped_multilingual.webm");
    // /* enable progress meter */
    // curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0);
    // /* progress callback  */
    // curl_easy_setopt(curl, CURLOPT_PROGRESSDATA, NULL);
    // curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, progress_callback);

    /* header callback */
    curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, header_callback);
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, NULL);

    /* chunk callback */
    fp = fopen("file.webm", "wb+");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, chunk_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

    //download
    res = curl_easy_perform(curl);
    if(fp)
    {
        fclose(fp);
    }
    //clean
    curl_easy_cleanup(curl);

exit:
    curl_global_cleanup();
    return 0;
}