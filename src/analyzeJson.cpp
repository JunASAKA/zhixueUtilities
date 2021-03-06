#include "jsonRewrite.hpp"



namespace analyzeJson
{

	std::string analyzeAnsJson(std::string inputJson)
	{

		std::string index;

		std::string priNum;
		std::string subNum;
		std::string child;
		//std::string ans;
		Json::CharReaderBuilder readerBuilder;
        JSONCPP_STRING errs;
		std::unique_ptr<Json::CharReader> reader(readerBuilder.newCharReader());
		Json::Value root;

		Json::Value finalout;

		if (reader->parse(inputJson.data(), inputJson.data() + inputJson.size(), &root, &errs))
		{
			const Json::Value sectionList = root["result"]["sectionList"];
			for (unsigned int i = 0; i < sectionList.size(); i++)
			{
				priNum = sectionList[i]["title"].asString();
				//std::cout << priNum<<std::endl;
				const Json::Value topicList = sectionList[i]["topicList"];
				for (unsigned int i = 0; i < topicList.size(); i++)
				{

					if (i < 100000)
					{
						index = std::string(5 - std::__cxx11::to_string(i).length(), '0') + std::__cxx11::to_string(i);
						index = "インデックスは" + index + "である。——";
					}
					else
					{
						index = std::__cxx11::to_string(i);
						index = "インデックスは" + index + "である。——";
					}

					subNum = index + topicList[i]["title"].asString();
					//std::cout << subNum<<std::endl;

					const Json::Value children = topicList[i]["children"];
					for (unsigned int i = 0; i < children.size(); i++)
					{

						child = std::__cxx11::to_string(i);
						const Json::Value answers = children[i]["answers"];
						if (answers.size() == 0)
						{
							finalout["答え"][priNum][subNum][child][i] = "null";
						}
						//std::cout << ans<<std::endl;

						else
						{
							for (unsigned int i = 0; i < answers.size(); i++)
							{

								//std::cout << ans<<std::endl;
								finalout["答え"][priNum][subNum][child][i] = answers[i].asString();
								//;
							}
						}
					}
				}
			}
			const Json::Value answerAttachments = root["result"]["answerAttachments"];
			for (unsigned int i = 0; i < answerAttachments.size(); i++)
			{
				finalout["答えの添付ファイル"][i] = answerAttachments[i]["path"].asString();
			}
		}
		else
		{
			std::cout << inputJson << std::endl;
			std::cout << errs << std::endl;
			return "";
		}

		return rewrite::toStyledStringRewrite(finalout);
	}

	std::string analyzeHwListJson(std::string inputJson)
	{

		Json::CharReaderBuilder readerBuilder;
        JSONCPP_STRING errs;
		std::unique_ptr<Json::CharReader> reader(readerBuilder.newCharReader());
		Json::Value root;
		Json::Value finalout;
		std::string index;

		if (reader->parse(inputJson.data(), inputJson.data() + inputJson.size(), &root, &errs))
		{
			//std::cout << root["result"]["list"].size() << std::endl;
			const Json::Value list = root["result"]["list"];
			for (unsigned int i = 0; i < list.size(); i++)
			{
				//std::cout << i << list[i]["hwTitle"].asString()<< list[i]["hwId"].asString()<<std::endl;
				if (i < 100000)
				{
					index = std::string(5 - std::__cxx11::to_string(i).length(), '0') + std::__cxx11::to_string(i);
					index = "インデックスは" + index + "である。";
				}
				else
				{
					index = std::__cxx11::to_string(i);
					index = "インデックスは" + index + "である。";
				}

				finalout[index]["Title"] = list[i]["hwTitle"].asString();
				finalout[index]["Homework ID"] = list[i]["hwId"].asString();
				finalout[index]["Student Homework ID"] = list[i]["stuHwId"].asString();
				finalout[index]["Subject"] = list[i]["subjectName"].asString();
				finalout[index]["State"] = list[i]["homeWorkState"]["stateName"].asString();
				finalout[index]["Type"] = list[i]["homeWorkTypeDTO"]["typeName"].asString();
				finalout[index]["Class ID"] = list[i]["classId"].asString();
			}
		}
		else
		{
			std::cout << inputJson << std::endl;
			std::cout << errs << std::endl;
			return "";
		}

		return rewrite::toStyledStringRewrite(finalout);
	}

	int analyzeIfSuccess(std::string str)
	{
		Json::CharReaderBuilder readerBuilder;
        JSONCPP_STRING errs;
		std::unique_ptr<Json::CharReader> reader(readerBuilder.newCharReader());
		Json::Value root;
		if (reader->parse(str.data(), str.data() + str.size(), &root, &errs))
		{
			if (root["code"].asString() == "000000" || root["code"].asString() == "success")
			{
				return 0;
			}
			else
			{
				return -1;
			}
		}
		else
		{
			std::cout << errs << std::endl;
			return -1;
		}
	}
	std::string index2hwId(std::string inputJson, std::string index)
	{
		Json::CharReaderBuilder readerBuilder;
        JSONCPP_STRING errs;
		std::unique_ptr<Json::CharReader> reader(readerBuilder.newCharReader());
		Json::Value root;
		index = "インデックスは" + index + "である。";
		if (reader->parse(inputJson.data(), inputJson.data() + inputJson.size(), &root, &errs))
		{
			return root[index]["Homework ID"].asString();
		}
		else
		{
			std::cout << errs << std::endl;
			return "";
		}
	}
	std::string index2stuHwId(std::string inputJson, std::string index)
	{
		Json::CharReaderBuilder readerBuilder;
        JSONCPP_STRING errs;
		std::unique_ptr<Json::CharReader> reader(readerBuilder.newCharReader());
		Json::Value root;
		index = "インデックスは" + index + "である。";
		if (reader->parse(inputJson.data(), inputJson.data() + inputJson.size(), &root, &errs))
		{
			return root[index]["Student Homework ID"].asString();
		}
		else
		{
			std::cout << errs << std::endl;
			return "";
		}
	}
	std::string index2classId(std::string inputJson, std::string index)
	{
		Json::CharReaderBuilder readerBuilder;
        JSONCPP_STRING errs;
		std::unique_ptr<Json::CharReader> reader(readerBuilder.newCharReader());
		Json::Value root;
		index = "インデックスは" + index + "である。";
		if (reader->parse(inputJson.data(), inputJson.data() + inputJson.size(), &root, &errs))
		{
			return root[index]["Class ID"].asString();
		}
		else
		{
			std::cout << errs << std::endl;
			return "";
		}
	}
	std::string index2typeName(std::string inputJson, std::string index)
	{
		Json::CharReaderBuilder readerBuilder;
        JSONCPP_STRING errs;
		std::unique_ptr<Json::CharReader> reader(readerBuilder.newCharReader());
		Json::Value root;
		index = "インデックスは" + index + "である。";
		if (reader->parse(inputJson.data(), inputJson.data() + inputJson.size(), &root, &errs))
		{
			return root[index]["Type"].asString();
		}
		else
		{
			std::cout << errs << std::endl;
			return "";
		}
	}
	std::string clkHwDetail2clockRecordId(std::string inputJson)
	{
		Json::CharReaderBuilder readerBuilder;
        JSONCPP_STRING errs;
		std::unique_ptr<Json::CharReader> reader(readerBuilder.newCharReader());
		Json::Value root;
		if (reader->parse(inputJson.data(), inputJson.data() + inputJson.size(), &root, &errs))
		{

			const Json::Value hwClockRecordPreviewResponses = root["result"]["hwClockRecordPreviewResponses"];
			return hwClockRecordPreviewResponses[0]["clockRecordId"].asString();
		}
		else
		{
			std::cout << inputJson << std::endl;
			std::cout << errs << std::endl;
			return "";
		}
	}
	std::string format(std::string inputJson)
	{
		Json::CharReaderBuilder readerBuilder;
        JSONCPP_STRING errs;
		std::unique_ptr<Json::CharReader> reader(readerBuilder.newCharReader());
		Json::Value root;
		if (reader->parse(inputJson.data(), inputJson.data() + inputJson.size(), &root, &errs))
		{

			return rewrite::toStyledStringRewrite(root);
		}
		else
		{
			std::cout << errs << std::endl;
			return "";
		}
	}

	std::string analyzeAttachJson(std::string inputJson){
		Json::CharReaderBuilder readerBuilder;
        JSONCPP_STRING errs;
		std::unique_ptr<Json::CharReader> reader(readerBuilder.newCharReader());
		Json::Value root;

		Json::Value finalout;
		std::string index;

		if (reader->parse(inputJson.data(), inputJson.data() + inputJson.size(), &root, &errs))
		{
			const Json::Value result = root["result"];
			for (unsigned int i = 0; i < result.size(); i++)
			{
				index = result[i]["sort"].asString();
				if (i < 100000)
				{
					index = std::string(5 - std::__cxx11::to_string(i).length(), '0') + std::__cxx11::to_string(i);
					index = "インデックスは" + index + "である。";
				}
				else
				{
					index = std::__cxx11::to_string(i);
					index = "インデックスは" + index + "である。";
				}

				//finalout["インデックスは"+result[i]["sort"].asString()+"である。"]=result[i]["sort"].asString();
				finalout[index]["タイトル"]=result[i]["name"].asString();
				finalout[index]["リンク"]=result[i]["path"].asString();
			}
			
			return rewrite::toStyledStringRewrite(finalout);
		}
		else
		{
			std::cout << errs << std::endl;
			return "";
		}
	}
}