#include "zhixueUtilities.hpp"
#include <jsoncpp/json/json.h>
#include <curl/curl.h>

namespace prepareSubmission
{

    std::string prepareSubmJson(std::string inputStr, std::string stuToken, std::string stuHwId)
    {

        std::string str = submissionTemplate(stuToken, stuHwId);

        std::string questionId;
        std::string childQuestionId;
        //std::string ans;
        Json::Reader reader;
        Json::Value root;

        Json::Value finalout;
        if (reader.parse(str.c_str(), finalout))
        {
            if (reader.parse(inputStr.c_str(), root))
            {
                const Json::Value sectionList = root["result"]["sectionList"];
                for (unsigned int i = 0; i < sectionList.size(); i++)
                {

                    const Json::Value topicList = sectionList[i]["topicList"];
                    for (unsigned int i = 0; i < topicList.size(); i++)
                    {

                        questionId = topicList[i]["questionId"].asString();

                        const Json::Value children = topicList[i]["children"];
                        for (unsigned int i = 0; i < children.size(); i++)
                        {
                            childQuestionId = children[i]["childQuestionId"].asString();

                            const Json::Value answers = children[i]["answers"];
                            if (answers.size() == 0)
                            {

                                Json::Value temp;
                                std::string tempe = "{\"answer\":\"\",\"attachments\":[],\"childQuestionId\":\"" + childQuestionId + "\",\"duration\":0,\"feedback\":0,\"questionId\":\"" + questionId + "\"}";
                                if (reader.parse(tempe.c_str(), temp))
                                {
                                    finalout["params"]["questions"].append(temp);
                                }
                            }

                            else
                            {
                                for (unsigned int i = 0; i < answers.size(); i++)
                                {

                                    Json::Value temp;
                                    std::string tempe = "{\"answer\":\"" + answers[i].asString() + "\",\"attachments\":[],\"childQuestionId\":\"" + childQuestionId + "\",\"duration\":0,\"feedback\":0,\"questionId\":\"" + questionId + "\"}";
                                    if (reader.parse(tempe.c_str(), temp))
                                    {
                                        finalout["params"]["questions"].append(Json::Value(temp));
                                    }
                                }
                            }
                        }
                    }
                }
            }
            else
            {
                printf("err");
            }
        }

        return finalout.toStyledString();
    }

    std::string submissionTemplate(std::string stuToken, std::string stuHwId)
    {

        std::string finalout = "{\"base\":{\"Authorization\":\""+stuToken+"\",\"appId\":\"OAXI57PG\",\"appVersion\":\"2.0.1542\",\"packageName\":\"com.iflytek.elpmobile.student\",\"sysType\":\"Android\",\"sysVersion\":\"Nashi\",\"udid\":\"0\",\"userId\":\"0\",\"utag\":\"\"},\"params\":{\"duration\":0,\"questions\":[],\"stuHwId\":\""+stuHwId+"\",\"submitType\":\"SUBMIT\"}}";
        return finalout;
    }



}