#pragma once

#include <iostream>
#include <string.h>

#define postAnsURL "https://mhw.zhixue.com/hw/manage/homework/redeploy"
#define redoURL "https://mhw.zhixue.com/hw/correction/redo"

namespace analyzeJson
{
    std::string analyzeAnsJson(std::string inputJson);
    std::string analyzeHwListJson(std::string inputJson);
    int analyzeIfRedoSuccess(std::string str);
}

namespace reqData
{
    size_t CurlWrite_CallbackFunc_StdString(void *contents, size_t size, size_t nmemb, std::string *s);
    std::string postAnsJson(std::string tchToken, std::string hwId);

    std::string getHwListJson(std::string stuToken);
    std::string redoHomework(std::string tchToken, std::string userId, std::string hwId);

}
