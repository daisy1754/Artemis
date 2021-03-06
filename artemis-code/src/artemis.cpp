/*
 * Copyright 2012 Aarhus University
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <iostream>
#include <stdlib.h>
#include <getopt.h>
#include <string>
#include <QDir>
#include <QUrl>
#include <QApplication>

#include "exceptionhandlingqapp.h"
#include "runtime/options.h"
#include "artemisapplication.h"
#include "util/loggingutil.h"
#include "artemisglobals.h"

using namespace std;

QUrl parseCmd(int argc, char* argv[], artemis::Options& options)
{

    std::string usage = "\n"
            "artemis [-i <n>][-c <URL>][-t <URL>][-r][-u][-p <path>] <url>\n"
            "\n"
            "Test the JavaScript application found at <url>.\n"
            "\n"
            "-i <n>   : Iterations - Artemis will generate and execute <n>\n"
            "           sequences of events. Default is 4.\n"
            "\n"
            "-f #<formElementId>=<formElementValue> : Set the form element with ID #<formElementId> to the value <formElementValue> at each iteration. Remember to write the # for the element ID."
            "\n"
            "-c <URl> : Cookies - // TODO\n"
            "\n"
            "-t <URL>:<PORT> : Set proxy\n"
            "\n"
            "-r       : set_recreate_page(true) // TODO\n"
            "\n"
            "-p       : dump_page_states(<path>) // TODO\n"
            "\n"
            "-s       : Enable DOM state checking\n"
            "\n"
            "-e       : Negate the last solved PC printet to stdout (used for testing)\n"
            "\n"
            "--major-mode <mode>:\n"
            "           The major-mode specifies the top-level test algorithm used by Artemis.\n"
            "\n"
            "           artemis - (default) the top-level test algorithm described in the ICSE'11 Artemis paper\n"
            "           manual - open a browser window for manual testing of web applications\n"
            "           concolic - perform an automated concolic analysis of form validation code\n"
            "\n"
            "--strategy-form-input-generation <strategy>:\n"
            "           Select form input generation strategy.\n"
            "\n"
            "           javascript-constants - select form inputs based in observed JavaScript constants\n"
            "           random - (default) random inputs\n"
            "\n"
            "--coverage-report <report-type>:\n"
            "           Select code coverage report formatting.\n"
            "\n"
            "           html - HTML report dumped in the folder you run Artemis from\n"
            "           stdout - text report is printed to std out\n"
            "           none - (default) code coverage report is omitted\n"
            "\n"
            "--coverage-report-ignore <URL>:\n"
            "           Exclude the given URL from the coverage report and coverage statistics.\n"
            "\n"
            "--path-trace-report <report-type>:\n"
            "           Output a report of the execution path through the covered JavaScript.\n"
            "\n"
            "           all - All executed paths are displayed\n"
            "           click - Only paths beginning with a click event are displayed\n"
            "           none - (default) Path trace report is omitted\n"
            "           html - HTML trace report is generated in the folder you run Artemis from\n"
            "\n"
            "--path-trace-report-bytecode true|false:\n"
            "\n"
            "           Show executed bytecodes in path trace reports. Default is false.\n"
            "\n"
            "--concolic-tree-output <trees>:\n"
            "           none - Do not output any graphs.\n"
            "           final (default) - Generate a graph of the final tree after analysis.\n"
            "           all - Generate a graph of the tree at every iteration.\n"
            "\n"
            "--strategy-priority <strategy>:\n"
            "           Select priority strategy.\n"
            "\n"
            "           constant - (default) assign the same priority to new configurations\n"
            "           random - assign a random priority to new configurations\n"
            "           coverage - assign higher priority to configurations with low coverage\n"
            "           readwrite - use read/write-sets for JavaScript properties to assign priorities\n"
            "\n"
            "--input-strategy-same-length <num>:\n"
            "           Set the number of permutations of an executed sequence (of same length) generated by the input generator."
            "\n"
            "--function-call-heap-report all | named | none\n"
            "           Writes a report containing heaps before all or named functioncalls.\n"
            "--function-call-heap-report-random-factor <int>\n"
            "           When faced with many function calls, this parameter saves data with a factor <int>^-1"
            "\n";

    struct option long_options[] = {
    {"strategy-form-input-generation", required_argument, NULL, 'x'},
    {"coverage-report", required_argument, NULL, 'y'},
    {"strategy-priority", required_argument, NULL, 'z'},
    {"input-strategy-same-length", required_argument, NULL, 'j'},
    {"coverage-report-ignore", required_argument, NULL, 'k'},
    {"major-mode", required_argument, NULL, 'm'},
    {"path-trace-report", required_argument, NULL, 'a'},
    {"path-trace-report-bytecode", required_argument, NULL, 'b'},
    {"function-call-heap-report", required_argument, NULL, 'g'},
    {"function-call-heap-report-random-factor", required_argument, NULL, 'l'},
    {"concolic-tree-output", required_argument, NULL, 'd'},
    {"help", no_argument, NULL, 'h'},
    {0, 0, 0, 0}
    };

    int option_index = 0;
    char c;
    artemis::Log::addLogLevel(artemis::INFO);
    artemis::Log::addLogLevel(artemis::FATAL);

    while ((c = getopt_long(argc, argv, "ehsrp:a:m:f:t:c:i:v:", long_options, &option_index)) != -1) {

        switch (c) {

        case 'h': {
            std::cout << usage;
            exit(0);
        }

        case 'f': {

            QString input = QString(optarg);

            int lastEqualsIndex = QString(optarg).lastIndexOf("=");
            Q_ASSERT(lastEqualsIndex >= 0);

            options.presetFormfields.insert(input.left(lastEqualsIndex), input.mid(lastEqualsIndex+1));
            break;
        }

        case 'p': {
            QDir ld = QDir(QString(optarg));
            options.dumpPageStates = "k";
            break;
        }

        case 'r': {
            options.recreatePage = true;
            break;
        }

        case 't': {
            options.useProxy = QString(optarg);
            break;
        }

        case 'c': {
            QStringList parts = QString(optarg).split("=");
            options.presetCookies.insert(parts.at(0), parts.at(1));
            break;
        }

        case 'i': {
            options.iterationLimit = QString(optarg).toInt();
            break;
        }

        case 'j': {
            options.numberSameLength = QString(optarg).toInt();
            break;
        }

        case 's': {
            options.disableStateCheck = false;
            break;
        }

        case 'x': {

            if (string(optarg).compare("javascript-constants") == 0) {
                options.formInputGenerationStrategy = artemis::ConstantString;
            } else if (string(optarg).compare("random") == 0) {
                options.formInputGenerationStrategy = artemis::Random;
            } else {
                cerr << "ERROR: Invalid strategy " << optarg << endl;
                exit(1);
            }

            break;

        }

        case 'y': {
            if (QString(optarg).toLower().compare("html") == 0) {
                options.outputCoverage = artemis::HTML;
            } else if (QString(optarg).toLower().compare("stdout") == 0) {
                options.outputCoverage = artemis::STDOUT;
            } else if (QString(optarg).toLower().compare("none") == 0) {
                options.outputCoverage = artemis::NONE;
            } else {
                cerr << "ERROR: Invalid choice of coverage report " << optarg << endl;
                exit(1);
            }
            break;
        }

        case 'k': {
            options.coverageIgnoreUrls.insert(QUrl(QString(optarg)));
            break;
        }

        case 'z': {
            if (string(optarg).compare("constant") == 0) {
                options.prioritizerStrategy = artemis::CONSTANT;
            } else if (string(optarg).compare("random") == 0) {
                options.prioritizerStrategy = artemis::RANDOM;
            } else if (string(optarg).compare("coverage") == 0) {
                options.prioritizerStrategy = artemis::COVERAGE;
            } else if (string(optarg).compare("readwrite") == 0) {
                options.prioritizerStrategy = artemis::READWRITE;
            } else if (string(optarg).compare("all") == 0){
                options.prioritizerStrategy = artemis::ALL_STRATEGIES;
            } else {
                cerr << "ERROR: Invalid choice of prioritizer strategy " << optarg << endl;
                exit(1);
            }

            break;
        }

         case 'v': {
            artemis::Log::addLogLevel(artemis::OFF);

            if(QString(optarg).indexOf("debug",0,Qt::CaseInsensitive)>=0){
                artemis::Log::addLogLevel(artemis::DEBUG);
            }

            if(QString(optarg).indexOf("warning",0,Qt::CaseInsensitive)>=0){
                artemis::Log::addLogLevel(artemis::WARNING);
            }
            if(QString(optarg).indexOf("error",0,Qt::CaseInsensitive)>=0){
                artemis::Log::addLogLevel(artemis::ERROR);
            }
            if(QString(optarg).indexOf("fatal",0,Qt::CaseInsensitive)>=0){
                artemis::Log::addLogLevel(artemis::FATAL);
            }

            if(QString(optarg).indexOf("all",0,Qt::CaseInsensitive)>=0){
                artemis::Log::addLogLevel(artemis::ALL);
            }

            if(QString(optarg).indexOf("off",0,Qt::CaseInsensitive)>=0){
                artemis::Log::addLogLevel(artemis::OFF);

            }

            break;
        }

        case 'm': {

            if (string(optarg).compare("artemis") == 0) {
                options.majorMode = artemis::AUTOMATED;
            } else if (string(optarg).compare("manual") == 0) {
                options.majorMode = artemis::MANUAL;
            } else if (string(optarg).compare("concolic") == 0) {
                options.majorMode = artemis::CONCOLIC;
            } else {
                cerr << "ERROR: Invalid choice of major-mode " << optarg << endl;
                exit(1);
            }

            break;
        }

        case 'a': {

            if (string(optarg).compare("all") == 0) {
                options.reportPathTrace  = artemis::ALL_TRACES;
            } else if (string(optarg).compare("click") == 0) {
                options.reportPathTrace = artemis::CLICK_TRACES;
            } else if (string(optarg).compare("none") == 0) {
                options.reportPathTrace = artemis::NO_TRACES;
            }else if (string(optarg).compare("html") == 0) {
                options.reportPathTrace = artemis::HTML_TRACES;
            } else {
                cerr << "ERROR: Invalid choice of path-trace-report " << optarg << endl;
                exit(1);
            }

            break;
        }

        case 'b': {

            if (string(optarg).compare("true") == 0) {
                options.reportPathTraceBytecode  = true;
            } else if (string(optarg).compare("false") == 0) {
                options.reportPathTraceBytecode = false;
            } else {
                cerr << "ERROR: Invalid choice of path-trace-report-bytecode " << optarg << endl;
                exit(1);
            }

            break;
        }

 case 'g' : {
            if(string(optarg).compare("all") == 0){
                options.reportHeap = artemis::ALL_CALLS;
            } else if (string(optarg).compare("named") == 0){
                options.reportHeap = artemis::NAMED_CALLS;
            } else if (string(optarg).compare("none") == 0){

            } else {
                cerr << "ERROR: Invalid choice of function-call-heap-report " << optarg << endl;
                exit(1);
            }
            break;
        }
        case 'l' : {
            options.heapReportFactor = std::max(QString(optarg).toInt(), 1);
            break;
        }
        case 'd': {

            if (string(optarg).compare("none") == 0) {
                options.concolicTreeOutput = artemis::TREE_NONE;
            } else if (string(optarg).compare("final") == 0) {
                options.concolicTreeOutput = artemis::TREE_FINAL;
            } else if (string(optarg).compare("all") == 0) {
                options.concolicTreeOutput = artemis::TREE_ALL;
            } else {
                cerr << "ERROR: Invalid choice of concolic-tree-output " << optarg << endl;
                exit(1);
            }

            break;
        }

        case 'e': {
            options.concolicNegateLastConstraint = true;

            break;
        }

        }
    }

    QUrl url;

    if (optind >= argc) {
        // If we are in manual mode then the url is optional.
        if(options.majorMode != artemis::MANUAL){
            cerr << "Error: You must specify a URL" << endl;
            exit(1);
        }else{
            url = artemis::examplesIndexUrl();
        }

    }else{

        QStringList rawurl = QString(argv[optind]).split("@");
        url = rawurl.last();

        if (options.useProxy.length() > 0 && url.host() == "localhost") {
            cerr << "Error: You can not use the proxy setting in Artemis for content hosted on localhost" << endl;
            exit(1);
        }

        if (url.scheme().isEmpty()) {
            // the http:// part is missing
            url = QUrl("http://" + url.toString());
        }

        if (!url.isValid()) {
            cerr << "Error: The URL " << url.toString().toStdString() << " is not valid" << endl;
            exit(1);
        }

        if (rawurl.size() > 1) {
            QStringList rawauth = rawurl.first().split(":");
            url.setUserName(rawauth.first());
            url.setPassword(rawauth.last());
        }

    }

    return url;
}

void artemisConsoleMessageHandler(QtMsgType type, const char* msg)
{
    switch (type) {
    case QtDebugMsg:
        artemis::Log::debug(QString(msg).toStdString());
        break;
    case QtWarningMsg:
        artemis::Log::warning("Warning: "+QString(msg).toStdString());
        break;
    case QtCriticalMsg:
        artemis::Log::error("Critical: "+QString(msg).toStdString());
        break;
    case QtFatalMsg:
        artemis::Log::fatal("Fatal: "+QString(msg).toStdString());
        abort();
    }
}

int main(int argc, char* argv[])
{
    qInstallMsgHandler(artemisConsoleMessageHandler);

    ExceptionHandlingQApp app(argc, argv);

    artemis::Options options;
    QUrl url = parseCmd(argc, argv, options);

    artemis::ArtemisApplication artemisApp(0, &app, options, url);
    artemisApp.run(url);

    return app.exec();
}
