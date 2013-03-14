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
#include "pathtracer.h"
#include "util/loggingutil.h"


namespace artemis{

PathTracer::PathTracer()
{
    mTraces = QList<PathTrace>();
}

void PathTracer::notifyStartingLoad()
{
    newPathTrace("Starting Page Load");
}

void PathTracer::notifyStartingEvent(QSharedPointer<const BaseInput> inputEvent)
{
    newPathTrace("Starting Event: " + (inputEvent->toString()));
}

void PathTracer::slJavascriptFunctionCalled(QString functionName, size_t bytecodeSize, uint sourceOffset, QUrl sourceUrl, uint sourceStartLine)
{
    functionName = functionName.isEmpty() ? "<no name>" : (functionName + "()"); // Anonymous function??
    appendItem(FUNCALL, functionName);
}

void PathTracer::slJavascriptFunctionReturned(QString functionName, size_t bytecodeSize, uint sourceOffset, QUrl sourceUrl, uint sourceStartLine)
{
    functionName = functionName.isEmpty() ? "<no name>" : (functionName + "()"); // Anonymous function??
    appendItem(FUNRET, functionName);
}

void PathTracer::slEventListenerTriggered(QWebElement* elem, QString eventName)
{
    newPathTrace("Received Event: " + eventName + " on " + elem->tagName());
}

void PathTracer::newPathTrace(QString event)
{
    QList<QPair<PathTracer::ItemType, QString> > nl = QList<QPair<PathTracer::ItemType, QString> >();
    PathTrace newTrace = qMakePair(event, nl);
    mTraces.append(newTrace);
}

void PathTracer::appendItem(ItemType type, QString message)
{
    if(mTraces.isEmpty()){
        newPathTrace("<onload>");
    }
    mTraces.last().second.append(qMakePair(type, message));
}

/**
  Note that this function implies a call graph which is not *necessarily* accurate.
  The function traces are given in chronological order, so if we ever get calls which are not sequential or
  for some reason we miss one then we will guess
**/
void PathTracer::write()
{
    QPair<ItemType,QString> item;
    PathTrace trace;
    uint stackLevel;

    //Log::info("===== Path Tracer =====");
    if(mTraces.isEmpty()){
        Log::info("No traces were recorded");
        return;
    }
    foreach(trace, mTraces){
        Log::info("Trace: " + trace.first.toStdString());
        stackLevel = 0;
        foreach(item, trace.second){
            switch(item.first){
            case FUNCALL:
                Log::info("  Function Call: " + std::string(stackLevel*2, ' ') + item.second.toStdString());
                stackLevel++;
                break;
            case FUNRET:
                stackLevel--;
                //Log::info("  Function End:  " + std::string(stackLevel*2, ' ') + item.second.toStdString());
                break;
            default:
                Log::info("  Unknown:       " + item.second.toStdString());
                break;
            }
        }
    }
}

}
