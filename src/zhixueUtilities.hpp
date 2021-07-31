#pragma once

#include <iostream>
#include <string.h>

#define postAnsURL "https://mhw.zhixue.com/hw/manage/homework/redeploy"
#define redoURL "https://mhw.zhixue.com/hw/correction/redo"
#define submitURL "https://mhw.zhixue.com/hw/answer/homework/submit"

namespace analyzeJson
{
    std::string analyzeAnsJson(std::string inputJson);
    std::string analyzeHwListJson(std::string inputJson);
    int analyzeIfSuccess(std::string str);
    std::string index2stuHwId(std::string inputJson, std::string index);
    std::string index2hwId(std::string inputJson, std::string index);
}

namespace reqData
{
    size_t CurlWrite_CallbackFunc_StdString(void *contents, size_t size, size_t nmemb, std::string *s);
    std::string postAnsJson(std::string tchToken, std::string hwId);

    std::string getHwListJson(std::string stuToken, bool completed);
    std::string redoHomework(std::string tchToken, std::string userId, std::string hwId);

    std::string sendSubbmission(std::string POSTFIELDS, std::string stuToken);

}

namespace submission
{
    std::string prepareSubmJson(std::string inputStr, std::string stuToken, std::string stuHwId);
    std::string submissionTemplate(std::string stuToken, std::string stuHwId);
    std::string prepareReviJson(std::string inputStr, std::string stuToken, std::string stuHwId);
    std::string revisionTemplate(std::string stuToken, std::string stuHwId);
    std::string submissionPipeline(std::string tchToken, std::string hwId, std::string stuToken, std::string stuHwId);
    std::string automationPipeline(std::string tchToken, std::string hwId, std::string stuToken, std::string stuId, std::string stuHwId);
    std::string revisionPipeline(std::string tchToken, std::string hwId, std::string stuToken, std::string stuHwId);
}