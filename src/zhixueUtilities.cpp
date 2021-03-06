#include "clipp.hpp"
#include "zhixueUtilities.hpp"
#include <cstdlib>

bool _EMIT_UTF8 = true;
int main(int argc, char *argv[])
{
	enum class mode
	{
		getList,
		getAns,
		getAttach,
		redoHomework,
		submitHomework,
		automation,
		autoRevise,
		availablize,
		showSubmitDetail,
		help
	};
	mode selected = mode::help;

	//std::string tchToken;
	//std::string stuToken;
	std::string hwId;
	std::string stuId;
	std::string stuHwId;
	std::string listIndex;
	std::string stuUsername;
	std::string stuPasswd;
	std::string tchUsername;
	std::string tchPasswd;
	std::string attachmentUrl;
	std::string clazzId;

	//std::string finaloutStr;

	bool useIndex = false;
	bool completed = false;
	bool isClkHw = false;
	//bool useClazzId = false;
	bool redoWithStuId = false;

	auto getListMode = (clipp::command("getList").set(selected, mode::getList),
						clipp::option("-stu", "--student-login") & clipp::value("stuUsername", stuUsername) % "Student's username" & clipp::value("stuPasswd", stuPasswd) % "Student's encoded Psssword",
						clipp::option("--already-done").set(completed, true).doc("use the list of completed homeworks"));

	auto getAnsMode = (clipp::command("getAns").set(selected, mode::getAns),
					   clipp::option("-tch", "--teacher-login") & clipp::value("tchUsername", tchUsername) % "ANY Teacher's Username" & clipp::value("tchPasswd", tchPasswd) % "THE Teacher's encoded Password",
					   clipp::option("-hi", "--homework-id") & clipp::value("hwId", hwId) % "Homework ID",
					   clipp::option("-stu", "--student-login") & clipp::value("stuUsername", stuUsername) % "Student's username" & clipp::value("stuPasswd", stuPasswd) % "Student's encoded Psssword",
					   clipp::option("--index").set(useIndex, true) & clipp::value("listIndex", listIndex) % "List Index",
					   clipp::option("--already-done").set(completed, true).doc("use the list of completed homeworks"));

	auto getAttachMode = (clipp::command("getAttachment").set(selected, mode::getAttach),
						  clipp::option("-stu", "--student-login") & clipp::value("stuUsername", stuUsername) % "Student's username" & clipp::value("stuPasswd", stuPasswd) % "Student's encoded Psssword",
						  clipp::option("-hi", "--homework-id") & clipp::value("hwId", hwId) % "Homework ID",
						  clipp::option("--index").set(useIndex, true) & clipp::value("listIndex", listIndex) % "List Index",
						  clipp::option("--already-done").set(completed, true).doc("use the list of completed homeworks")

	);

	auto redoMode = (clipp::command("redo").set(selected, mode::redoHomework),
					 clipp::option("-tch", "--teacher-login") & clipp::value("tchUsername", tchUsername) % "ANY Teacher's Username" & clipp::value("tchPasswd", tchPasswd) % "THE Teacher's encoded Password",
					 clipp::option("-stu", "--student-login") & clipp::value("stuUsername", stuUsername) % "Student's username" & clipp::value("stuPasswd", stuPasswd) % "Student's encoded Psssword",
					 clipp::option("-hi", "--homework-ids") & clipp::value("hwId", hwId) % "Homework ID" & clipp::value("stuHwId", stuHwId) % "Student Homework ID",
					 clipp::option("-stu", "--student-login") & clipp::value("stuUsername", stuUsername) % "Student's username" & clipp::value("stuPasswd", stuPasswd) % "Student's encoded Psssword",
					 clipp::option("--index").set(useIndex, true) & clipp::value("listIndex", listIndex) % "List Index",
					 clipp::option("--already-done").set(completed, true).doc("use the list of completed homeworks"),
					 clipp::option("--is-clock-homework").set(isClkHw, true).doc("redo the clock homework"),
					 clipp::option("--student-id").set(redoWithStuId, true).doc("redo with student id") & clipp::value("stuId", stuId) % "Student Id");

	auto submitMode = (clipp::command("autoSubmit").set(selected, mode::submitHomework),
					   clipp::option("-tch", "--teacher-login") & clipp::value("tchUsername", tchUsername) % "ANY Teacher's Username" & clipp::value("tchPasswd", tchPasswd) % "THE Teacher's encoded Password",
					   clipp::option("-stu", "--student-login") & clipp::value("stuUsername", stuUsername) % "Student's username" & clipp::value("stuPasswd", stuPasswd) % "Student's encoded Psssword",
					   clipp::option("-hi", "--homework-ids") & clipp::value("hwId", hwId) % "Homework ID" & clipp::value("stuHwId", stuHwId) % "Student Homework ID",
					   clipp::option("--index").set(useIndex, true) & clipp::value("listIndex", listIndex) % "List Index",
					   clipp::option("--with-attachment") & clipp::value("attachmentUrl", attachmentUrl) % "Attachmenet URL, only supports pics, maybe",
					   clipp::option("--already-done").set(completed, true).doc("use the list of completed homeworks"));

	auto reviseMode = (clipp::command("autoRevise").set(selected, mode::autoRevise),
					   clipp::option("-tch", "--teacher-login") & clipp::value("tchUsername", tchUsername) % "ANY Teacher's Username" & clipp::value("tchPasswd", tchPasswd) % "THE Teacher's encoded Password",
					   clipp::option("-stu", "--student-login") & clipp::value("stuUsername", stuUsername) % "Student's username" & clipp::value("stuPasswd", stuPasswd) % "Student's encoded Psssword",
					   clipp::option("-hi", "--homework-ids") & clipp::value("hwId", hwId) % "Homework ID" & clipp::value("stuHwId", stuHwId) % "Student Homework ID",
					   clipp::option("--index").set(useIndex, true) & clipp::value("listIndex", listIndex) % "List Index",
					   clipp::option("--with-attachment") & clipp::value("attachmentUrl", attachmentUrl) % "Attachmenet URL, only supports pics, maybe",
					   clipp::option("--already-done").set(completed, true).doc("use the list of completed homeworks"));

	auto autoMode = (clipp::command("automation").set(selected, mode::automation),
					 clipp::option("-tch", "--teacher-login") & clipp::value("tchUsername", tchUsername) % "ANY Teacher's Username" & clipp::value("tchPasswd", tchPasswd) % "THE Teacher's encoded Password",
					 clipp::option("-stu", "--student-login") & clipp::value("stuUsername", stuUsername) % "Student's username" & clipp::value("stuPasswd", stuPasswd) % "Student's encoded Psssword",
					 clipp::option("-hi", "--homework-ids") & clipp::value("hwId", hwId) % "Homework ID" & clipp::value("stuHwId", stuHwId) % "Student Homework ID",
					 clipp::option("--index").set(useIndex, true) & clipp::value("listIndex", listIndex) % "List Index",
					 clipp::option("--with-attachment") & clipp::value("attachmentUrl", attachmentUrl) % "Attachmenet URL, only supports pics, maybe",
					 clipp::option("--already-done").set(completed, true).doc("use the list of completed homeworks"));

	auto availMode = (clipp::command("availablize").set(selected, mode::availablize),
					  clipp::option("-tch", "--teacher-login") & clipp::value("tchUsername", tchUsername) % "ANY Teacher's Username" & clipp::value("tchPasswd", tchPasswd) % "THE Teacher's encoded Password",
					  clipp::option("-stu", "--student-login") & clipp::value("stuUsername", stuUsername) % "Student's username" & clipp::value("stuPasswd", stuPasswd) % "Student's encoded Psssword",
					  clipp::option("-hi", "--homework-id") & clipp::value("hwId", hwId) % "Homework ID",
					  clipp::option("--index").set(useIndex, true) & clipp::value("listIndex", listIndex) % "List Index",
					  clipp::option("--already-done").set(completed, true).doc("use the list of completed homeworks"));

	auto showDeatilMode = (clipp::command("showSubmitDetail").set(selected, mode::showSubmitDetail),
						   clipp::option("-tch", "--teacher-login") & clipp::value("tchUsername", tchUsername) % "ANY Teacher's Username" & clipp::value("tchPasswd", tchPasswd) % "THE Teacher's encoded Password",
						   clipp::option("-stu", "--student-login") & clipp::value("stuUsername", stuUsername) % "Student's username" & clipp::value("stuPasswd", stuPasswd) % "Student's encoded Psssword",
						   clipp::option("-hi", "--homework-ids") & clipp::value("hwId", hwId) % "Homework ID" & clipp::value("stuHwId", stuHwId) % "Student Homework ID",
						   clipp::option("--index").set(useIndex, true) & clipp::value("listIndex", listIndex) % "List Index",
						   clipp::option("--already-done").set(completed, true).doc("use the list of completed homeworks"));

	auto cli = ((getListMode | getAnsMode | redoMode | submitMode | reviseMode | autoMode | availMode | showDeatilMode | getAttachMode | clipp::command("help").set(selected, mode::help)),
				clipp::option("--no-emitting-utf8").call([]
														 { _EMIT_UTF8 = false; })
					.doc("do not emit utf8 when printing json"),
				clipp::option("-v", "--version").call([]
													  { std::cout << "version 5.12b" << std::endl; })
					.doc("show version"),
				clipp::option("-h", "--help").set(selected, mode::help).doc("show this help message"));

	if (parse(argc, argv, cli))
	{
		if (std::getenv("stuUsername") != nullptr)
		{
			stuUsername = std::getenv("stuUsername");
		}
		if (std::getenv("stuPasswd") != nullptr)
		{
			stuPasswd = std::getenv("stuPasswd");
		}
		if (std::getenv("tchUsername") != nullptr)
		{
			tchUsername = std::getenv("tchUsername");
		}
		if (std::getenv("tchPasswd") != nullptr)
		{
			tchPasswd = std::getenv("tchPasswd");
		}
		switch (selected)
		{
		case mode::getList:
			if (stuUsername.empty() || stuPasswd.empty())
			{
				std::cout << "?????????????????????????????????????????????????????????" << std::endl;
				break;
			}
			else
			{
				std::cout << analyzeJson::analyzeHwListJson(reqData::getHwListJson(login::finalout2Token(login::stuLoginPipeline(stuUsername, stuPasswd)), completed)) << std::endl;
			}

			break;
		case mode::getAns:
			if (tchUsername.empty() || tchPasswd.empty())
			{
				std::cout << "?????????????????????????????????????????????????????????" << std::endl;
				break;
			}
			else
			{
				if (useIndex)
				{
					if (stuUsername.empty() || stuPasswd.empty())
					{
						std::cout << "?????????????????????????????????????????????????????????" << std::endl;
						break;
					}
					else
					{
						std::string inputJson = analyzeJson::analyzeHwListJson(reqData::getHwListJson(login::finalout2Token(login::stuLoginPipeline(stuUsername, stuPasswd)), completed));
						hwId = analyzeJson::index2hwId(inputJson, listIndex);
						std::cout << analyzeJson::analyzeAnsJson(reqData::postAnsJson(login::finalout2Token(login::tchLoginPipeline(tchUsername, tchPasswd)), hwId)) << std::endl;
					}
				}
				else
				{
					if (hwId.empty())
					{
						std::cout << "??????????????????????????????????????????????????????" << std::endl;
						break;
					}
					else
					{
						std::cout << analyzeJson::analyzeAnsJson(reqData::postAnsJson(login::finalout2Token(login::tchLoginPipeline(tchUsername, tchPasswd)), hwId)) << std::endl;
					}
				}
			}

			break;
		case mode::getAttach:
			if (stuUsername.empty() || stuUsername.empty())
			{
				std::cout << "?????????????????????????????????????????????????????????" << std::endl;
				break;
			}
			else
			{
				if (useIndex)
				{
					std::string inputJson = analyzeJson::analyzeHwListJson(reqData::getHwListJson(login::finalout2Token(login::stuLoginPipeline(stuUsername, stuPasswd)), completed));
					hwId = analyzeJson::index2hwId(inputJson, listIndex);
					std::cout << analyzeJson::analyzeAttachJson(reqData::getAttachJson(login::finalout2Token(login::stuLoginPipeline(stuUsername, stuPasswd)), login::finalout2userId(login::stuLoginPipeline(stuUsername, stuPasswd)), hwId)) << std::endl;
				}
				else
				{

					std::cout << analyzeJson::analyzeAttachJson(reqData::getAttachJson(login::finalout2Token(login::stuLoginPipeline(stuUsername, stuPasswd)), login::finalout2userId(login::stuLoginPipeline(stuUsername, stuPasswd)), hwId)) << std::endl;
				}
			}
			break;
		case mode::redoHomework:
			if (tchUsername.empty() || tchPasswd.empty() || stuUsername.empty() || stuPasswd.empty())
			{
				std::cout << "?????????????????????????????????????????????????????????" << std::endl;
				break;
			}
			else
			{
				if (useIndex)
				{
					std::string inputJson = analyzeJson::analyzeHwListJson(reqData::getHwListJson(login::finalout2Token(login::stuLoginPipeline(stuUsername, stuPasswd)), completed));
					hwId = analyzeJson::index2hwId(inputJson, listIndex);
					stuHwId = analyzeJson::index2stuHwId(inputJson, listIndex);
					analyzeJson::index2typeName(inputJson, listIndex) == "????????????" ? isClkHw = true : isClkHw = false;
					if (redoWithStuId)
					{
						if (!isClkHw)
						{

							std::cout << reqData::redoHomework(login::finalout2Token(login::tchLoginPipeline(tchUsername, tchPasswd)), login::finalout2Token(login::stuLoginPipeline(stuUsername, stuPasswd)), stuId, hwId, isClkHw, stuHwId) << std::endl;
						}
						else
						{
							std::cout << "Clock Homework dosen't support this student id mode." << std::endl;
						}
					}
					else
					{
						std::cout << reqData::redoHomework(login::finalout2Token(login::tchLoginPipeline(tchUsername, tchPasswd)), login::finalout2Token(login::stuLoginPipeline(stuUsername, stuPasswd)), login::finalout2userId(login::stuLoginPipeline(stuUsername, stuPasswd)), hwId, isClkHw, stuHwId) << std::endl;
					}
				}
				else
				{
					if (hwId.empty() || stuHwId.empty())
					{
						std::cout << "??????????????????????????????????????????????????????" << std::endl;
						break;
					}
					else
					{
						if (redoWithStuId)
						{
							if (!isClkHw)
							{
								std::cout << reqData::redoHomework(login::finalout2Token(login::tchLoginPipeline(tchUsername, tchPasswd)), login::finalout2Token(login::stuLoginPipeline(stuUsername, stuPasswd)), stuId, hwId, isClkHw, stuHwId) << std::endl;
							}
							else
							{
								std::cout << "Clock Homework dosen't support this student id mode." << std::endl;
							}
						}
						else
						{
							std::cout << reqData::redoHomework(login::finalout2Token(login::tchLoginPipeline(tchUsername, tchPasswd)), login::finalout2Token(login::stuLoginPipeline(stuUsername, stuPasswd)), login::finalout2userId(login::stuLoginPipeline(stuUsername, stuPasswd)), hwId, isClkHw, stuHwId) << std::endl;
						}
					}
				}
			}
			break;
		case mode::submitHomework:
			if (tchUsername.empty() || tchPasswd.empty() || stuUsername.empty() || stuPasswd.empty())
			{
				std::cout << "?????????????????????????????????????????????????????????" << std::endl;
				break;
			}
			else
			{
				if (useIndex)
				{
					std::string inputJson = analyzeJson::analyzeHwListJson(reqData::getHwListJson(login::finalout2Token(login::stuLoginPipeline(stuUsername, stuPasswd)), completed));
					hwId = analyzeJson::index2hwId(inputJson, listIndex);
					stuHwId = analyzeJson::index2stuHwId(inputJson, listIndex);
					std::cout << submission::submissionPipeline(login::finalout2Token(login::tchLoginPipeline(tchUsername, tchPasswd)), hwId, login::finalout2Token(login::stuLoginPipeline(stuUsername, stuPasswd)), stuHwId, attachmentUrl) << std::endl;
				}
				else
				{
					if (hwId.empty() || stuHwId.empty())
					{
						std::cout << "??????????????????????????????????????????????????????" << std::endl;
						break;
					}
					else
					{
						std::cout << submission::submissionPipeline(login::finalout2Token(login::tchLoginPipeline(tchUsername, tchPasswd)), hwId, login::finalout2Token(login::stuLoginPipeline(stuUsername, stuPasswd)), stuHwId, attachmentUrl) << std::endl;
					}
				}
			}
			break;
		case mode::autoRevise:
			if (tchUsername.empty() || tchPasswd.empty() || stuUsername.empty() || stuPasswd.empty())
			{
				std::cout << "?????????????????????????????????????????????????????????" << std::endl;
				break;
			}
			else
			{
				if (useIndex)
				{
					std::string inputJson = analyzeJson::analyzeHwListJson(reqData::getHwListJson(login::finalout2Token(login::stuLoginPipeline(stuUsername, stuPasswd)), completed));
					hwId = analyzeJson::index2hwId(inputJson, listIndex);
					stuHwId = analyzeJson::index2stuHwId(inputJson, listIndex);
					std::cout << submission::revisionPipeline(login::finalout2Token(login::tchLoginPipeline(tchUsername, tchPasswd)), hwId, login::finalout2Token(login::stuLoginPipeline(stuUsername, stuPasswd)), stuHwId, login::finalout2userId(login::stuLoginPipeline(stuUsername, stuPasswd)), attachmentUrl) << std::endl;
				}
				else
				{
					if (hwId.empty() || stuHwId.empty())
					{
						std::cout << "??????????????????????????????????????????????????????" << std::endl;
						break;
					}
					else
					{
						std::cout << submission::revisionPipeline(login::finalout2Token(login::tchLoginPipeline(tchUsername, tchPasswd)), hwId, login::finalout2Token(login::stuLoginPipeline(stuUsername, stuPasswd)), stuHwId, login::finalout2userId(login::stuLoginPipeline(stuUsername, stuPasswd)), attachmentUrl) << std::endl;
					}
				}
			}

			break;
		case mode::automation:
			if (tchUsername.empty() || tchPasswd.empty() || stuUsername.empty() || stuPasswd.empty())
			{
				std::cout << "?????????????????????????????????????????????????????????" << std::endl;
				break;
			}
			else
			{
				if (useIndex)
				{
					std::string inputJson = analyzeJson::analyzeHwListJson(reqData::getHwListJson(login::finalout2Token(login::stuLoginPipeline(stuUsername, stuPasswd)), completed));
					hwId = analyzeJson::index2hwId(inputJson, listIndex);
					stuHwId = analyzeJson::index2stuHwId(inputJson, listIndex);
					std::cout << submission::automationPipeline(login::finalout2Token(login::tchLoginPipeline(tchUsername, tchPasswd)), hwId, login::finalout2Token(login::stuLoginPipeline(stuUsername, stuPasswd)), login::finalout2userId(login::stuLoginPipeline(stuUsername, stuPasswd)), stuHwId, attachmentUrl) << std::endl;
				}
				else
				{
					std::cout << submission::automationPipeline(login::finalout2Token(login::tchLoginPipeline(tchUsername, tchPasswd)), hwId, login::finalout2Token(login::stuLoginPipeline(stuUsername, stuPasswd)), login::finalout2userId(login::stuLoginPipeline(stuUsername, stuPasswd)), stuHwId, attachmentUrl) << std::endl;
				}
			}
			break;

		case mode::availablize:
			if (tchUsername.empty() || tchPasswd.empty())
			{
				std::cout << "?????????????????????????????????????????????????????????" << std::endl;
				break;
			}
			else
			{
				if (useIndex)
				{
					if (stuUsername.empty() || stuPasswd.empty())
					{
						std::cout << "?????????????????????????????????????????????????????????" << std::endl;
						break;
					}
					else
					{
						std::string inputJson = analyzeJson::analyzeHwListJson(reqData::getHwListJson(login::finalout2Token(login::stuLoginPipeline(stuUsername, stuPasswd)), completed));
						hwId = analyzeJson::index2hwId(inputJson, listIndex);
						std::cout << operateHw::updateHwPipeline(login::finalout2Token(login::tchLoginPipeline(tchUsername, tchPasswd)), hwId) << std::endl;
					}
				}
				else
				{
					if (hwId.empty() || stuHwId.empty())
					{
						std::cout << "??????????????????????????????????????????????????????" << std::endl;
						break;
					}
					else
					{
						std::cout << operateHw::updateHwPipeline(login::finalout2Token(login::tchLoginPipeline(tchUsername, tchPasswd)), hwId) << std::endl;
					}
				}
			}
			break;
		case mode::showSubmitDetail:
			if (tchUsername.empty() || tchPasswd.empty())
			{
				std::cout << "?????????????????????????????????????????????????????????" << std::endl;
				break;
			}
			else
			{
				if (useIndex)
				{
					if (stuUsername.empty() || stuPasswd.empty())
					{
						std::cout << "?????????????????????????????????????????????????????????" << std::endl;
						break;
					}
					else
					{
						std::string inputJson = analyzeJson::analyzeHwListJson(reqData::getHwListJson(login::finalout2Token(login::stuLoginPipeline(stuUsername, stuPasswd)), completed));
						clazzId = analyzeJson::index2classId(inputJson, listIndex);
						hwId = analyzeJson::index2hwId(inputJson, listIndex);
						/*
						std::cout << "???????????????????????????" << std::endl;
						std::cout << analyzeJson::format(reqData::showHwSubmitDetail(login::finalout2Token(login::tchLoginPipeline(tchUsername, tchPasswd)), hwId, login::finalout2clazzId(login::stuLoginPipeline(stuUsername, stuPasswd)))) << std::endl;
						std::cout << "???????????????????????????" << std::endl;
						std::cout << analyzeJson::format(reqData::listQuestionView(login::finalout2Token(login::tchLoginPipeline(tchUsername, tchPasswd)), hwId, login::finalout2clazzId(login::stuLoginPipeline(stuUsername, stuPasswd)))) << std::endl;
					*/
						std::cout << operateHw::showSubmitDetailPipeline(login::finalout2Token(login::tchLoginPipeline(tchUsername, tchPasswd)), hwId, clazzId) << std::endl;
					}
				}
				else
				{
					if (hwId.empty())
					{
						std::cout << "??????????????????????????????????????????????????????" << std::endl;
						break;
					}
					else
					{
						/*
						std::cout << "???????????????????????????" << std::endl;
						std::cout << analyzeJson::format(reqData::showHwSubmitDetail(login::finalout2Token(login::tchLoginPipeline(tchUsername, tchPasswd)), hwId, login::finalout2clazzId(login::stuLoginPipeline(stuUsername, stuPasswd)))) << std::endl;
						std::cout << "???????????????????????????" << std::endl;
						std::cout << analyzeJson::format(reqData::listQuestionView(login::finalout2Token(login::tchLoginPipeline(tchUsername, tchPasswd)), hwId, login::finalout2clazzId(login::stuLoginPipeline(stuUsername, stuPasswd)))) << std::endl;
					*/
						clazzId = analyzeJson::index2classId(analyzeJson::analyzeHwListJson(reqData::getHwListJson(login::finalout2Token(login::stuLoginPipeline(stuUsername, stuPasswd)), completed)), listIndex);
						std::cout << operateHw::showSubmitDetailPipeline(login::finalout2Token(login::tchLoginPipeline(tchUsername, tchPasswd)), hwId, clazzId) << std::endl;
					}
				}
			}

			break;
		case mode::help:
			std::cout << clipp::make_man_page(cli, "zhixueUtilities") << std::endl;
			break;
		}
	}
	else
	{
		std::cout << clipp::make_man_page(cli, "zhixueUtilities") << std::endl;
	}

	return 0;
}
