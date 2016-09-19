//=============================================================================================================
/**
* @file     ssvepBCIScreen.h
* @author   Viktor Klüber <viktor.klueber@tu-ilmenau.de>;
*           Lorenz Esch <Lorenz.Esch@tu-ilmenau.de>;
*           Christoph Dinh <chdinh@nmr.mgh.harvard.edu>;
*           Matti Hamalainen <msh@nmr.mgh.harvard.edu>
* @version  1.0
* @date     May 2016
*
* @section  LICENSE
*
* Copyright (C) 2014, Lorenz Esch, Christoph Dinh and Matti Hamalainen. All rights reserved.
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
* @brief    Contains the declaration of the ssvepBCIScreen class.
*
*/

#ifndef SSVEPBCISCREEN_H
#define SSVEPBCISCREEN_H

//*************************************************************************************************************
//=============================================================================================================
// INCLUDES
//=============================================================================================================

#include "FormFiles/ssvepbcisetupstimuluswidget.h"
#include "ssvepbciflickeringitem.h"
#include "screenkeyboard.h"
#include "ssvepbci.h"

//*************************************************************************************************************
//=============================================================================================================
// QT INCLUDES
//=============================================================================================================

#include <QOpenGLWidget>
#include <QMediaPlayer>

//*************************************************************************************************************
//=============================================================================================================
// DEFINE NAMESPACE ssvepBCIScreen
//=============================================================================================================

namespace SSVEPBCIPLUGIN
{

//*************************************************************************************************************
//=============================================================================================================
// TypeDefs
//=============================================================================================================

typedef  QList<double>  MyQList;

//*************************************************************************************************************
//=============================================================================================================
// FORWARD DECLARATIONS
//=============================================================================================================

class SsvepBci;
class SsvepBciSetupStimulusWidget;

//=============================================================================================================
/**
* DECLARE CLASS SsvepBciScreen
*
* @brief The SsvepBciScreen class provides the subject screen. Contains the list of items which will be painted
* to screen automatically
*/
class SsvepBciScreen : public QOpenGLWidget
{
    Q_OBJECT

    friend class SsvepBciSetupStimulusWidget;           /**< permit SsvepBciSetupStimulusWidget getting full access */

public:
    //=========================================================================================================
    /**
     * constructs the SsvepBciScreen object
     *
     */
    SsvepBciScreen(QSharedPointer<SsvepBci> pSsvepBci, QSharedPointer<SsvepBciSetupStimulusWidget> pSsvepBciSetupStimulusWidget, QOpenGLWidget *parent = 0 );

    //=========================================================================================================
    /**
     * deconstructs the SsvepBciScreen object
     *
     */
    ~SsvepBciScreen();

public slots:
    void setClassResults(double classResult);
    void updateFrequencyList(MyQList freqList);
    void useScreenKeyboard(bool useKeyboard);
    void clearScreen();


private:
    QSharedPointer<SsvepBci>                        m_pSsvepBci;                        /**< pointer to referring SsvepBci class */
    QSharedPointer<SsvepBciSetupStimulusWidget>     m_pSsvepBciSetupStimulusWidget;     /**< pointer to referring SsvepBciSetupStimulusWidget class */

    // draw items
    QList<SsvepBciFlickeringItem>   m_Items;            /**< QList containing all flickering Items to be painted */
    QSharedPointer<ScreenKeyboard>  m_pScreenKeyboard;   /**< pointer that holds the Screen-keyboard */


    // classifiaction updates
    double                          m_dXPosCross;       /**< X position of reference cross */
    double                          m_dYPosCross;       /**< Y position of reference cross */
    double                          m_dStep;            /**< moving step increment for reference cross */
    QList<double>                   m_lFreqList;        /**< list of current flickering frequencies */
    QColor                          m_qCrossColor;      /**< color of the reference cross */
//    QMediaPlayer                    m_qBeep;            /**< beep sound for successful classifiaction */
    QPainter                        m_qPainter;         /**< painter for drawing items to the widget scene */
//    QString                         m_qSoundPath;       /**< path to sound file for recognition sound */

    bool                            m_bUseScreenKeyboard;    /**< flag for updating screen keayboard */
    bool                            m_bClearScreen;          /**< flag for clearing swap buffer */



protected:
    //=========================================================================================================
    /**
     * overwritten functions from the QOpenGLWidget class which will be called automatically
     *
     */
    void resizeGL(int w, int h);
    void paintGL();
    void initializeGL();

};


}//Namescpace

#endif // SSVEPBCISCREEN_H
