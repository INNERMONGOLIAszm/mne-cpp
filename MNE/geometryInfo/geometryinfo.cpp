//=============================================================================================================
/**
* @file     geometryinfo.cpp
* @author   Lars Debor <lars.debor@tu-ilmenau.de>;
*           Matti Hamalainen <msh@nmr.mgh.harvard.edu>
* @version  1.0
* @date     Mai, 2017
*
* @section  LICENSE
*
* Copyright (C) 2017, Lars Debor and Matti Hamalainen. All rights reserved.
*
* Redistribution and use in source and binary forms, with or without modification, are permitted provided that
* the following conditions are met:
*     * Redistributions of source code must retain the above copyright notice, this list of conditions and the
*       following disclaimer.
*     * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and
*       the following disclaimer in the documentation and/or other materials provided with the distribution.
*     * Neither the name of MNE-CPP authors nor the names of its contributors may be used
*       to endorse or promote products derived from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
* WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
* PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
* PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*
*
* @brief    GeometryInfo class definition.
*
*/


//*************************************************************************************************************
//=============================================================================================================
// INCLUDES
//=============================================================================================================
#include "geometryinfo.h"
#include <mne/mne_bem_surface.h>


//*************************************************************************************************************
//=============================================================================================================
// INCLUDES
//=============================================================================================================

#include <cmath>

//*************************************************************************************************************
//=============================================================================================================
// QT INCLUDES
//=============================================================================================================

#include <QtConcurrent/QtConcurrent>

//*************************************************************************************************************
//=============================================================================================================
// Eigen INCLUDES
//=============================================================================================================


//*************************************************************************************************************
//=============================================================================================================
// USED NAMESPACES
//=============================================================================================================

using namespace GEOMETRYINFO;
using namespace Eigen;
using namespace MNELIB;


//*************************************************************************************************************
//=============================================================================================================
// DEFINE GLOBAL METHODS
//=============================================================================================================


//*************************************************************************************************************
//=============================================================================================================
// DEFINE MEMBER METHODS
//=============================================================================================================



QSharedPointer<QVector<qint32> > GeometryInfo::projectSensor(const MNEBemSurface &inSurface, const QVector<Vector3d> &sensorPositions)
{
    QSharedPointer<QVector<qint32>> outputArray = QSharedPointer<QVector<qint32>>::create();

    qint32 cores = QThread::idealThreadCount();
    if (cores <= 0)
    {
        // assume that we have at least two available cores
        cores = 2;
    }

    const qint32 subArraySize = ceil(sensorPositions.size() / cores);

    //small input size no threads needed
    // @todo best method ?? 16 thread prozessor ?
    if(subArraySize <= 1)
    {
        *outputArray = nearestNeighbor(inSurface, sensorPositions.constBegin(),sensorPositions.constEnd());
        return outputArray;
    }
    // split input array + thread start
    QVector<QFuture<QVector<qint32>>> threads(cores - 1);
    qint32 beginOffset = subArraySize;
    qint32 endOffset = beginOffset + subArraySize;
    for(qint32 i = 0; i < threads.size(); ++i)
    {
        //last round
        if(i == threads.size() -1)
        {
            threads[i] = QtConcurrent::run(nearestNeighbor, inSurface, sensorPositions.constBegin() + beginOffset, sensorPositions.constEnd());
            break;
        }
        else
        {
            threads[i] = QtConcurrent::run(nearestNeighbor, inSurface, sensorPositions.constBegin() + beginOffset, sensorPositions.constBegin() + endOffset);
            beginOffset = endOffset;
            endOffset += subArraySize;
        }
    }
    //calc while waiting for other threads
    outputArray->append(nearestNeighbor(inSurface, sensorPositions.constBegin(), sensorPositions.constBegin() + subArraySize));

    //wait for threads to finish
    bool finished = false;
        while (!finished) {
            finished = true;
            for (const auto &f : threads) {
                if (f.isFinished() == false) {
                    finished = false;
                }
            }
            // @todo optimal value for this ?
            QThread::msleep(2);
    }
    //move sub arrays back into output
    for(qint32 i = 0; i < threads.size(); ++i)
    {
        outputArray->append(threads[i].result());
    }

    return outputArray;
}
//*************************************************************************************************************

QVector<qint32> GeometryInfo::nearestNeighbor(const MNEBemSurface &inSurface,  QVector<Vector3d>::const_iterator sensorBegin, QVector<Vector3d>::const_iterator sensorEnd)
{
    ///lin search sensor positions
    QVector<qint32> mappedSensors;
    mappedSensors.reserve(std::distance(sensorBegin, sensorEnd));

    for(auto sensor = sensorBegin; sensor != sensorEnd; ++sensor)
    {
        qint32 championId;
        double champDist = std::numeric_limits<double>::max();
        for(qint32 i = 0; i < inSurface.rr.rows(); ++i)
        {
            double dist = sqrt(squared(inSurface.rr(i, 0) - (*sensor)[0])  // x-cord
                    + squared(inSurface.rr(i, 1) - (*sensor)[1])    // y-cord
                    + squared(inSurface.rr(i, 2) - (*sensor)[2]));  // z-cord
            if(dist < champDist)
            {
                championId = i;
                champDist = dist;
            }
        }
        mappedSensors.push_back(championId);
    }
    return mappedSensors;
}
//*************************************************************************************************************



