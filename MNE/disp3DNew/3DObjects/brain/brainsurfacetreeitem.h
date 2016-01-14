//=============================================================================================================
/**
* @file     brainsurfacetreeitem.h
* @author   Lorenz Esch <Lorenz.Esch@tu-ilmenau.de>;
*           Matti Hamalainen <msh@nmr.mgh.harvard.edu>
* @version  1.0
* @date     November, 2015
*
* @section  LICENSE
*
* Copyright (C) 2015, Lorenz Esch and Matti Hamalainen. All rights reserved.
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
* @brief     BrainSurfaceTreeItem class declaration.
*
*/

#ifndef BRAINSURFACETREEITEM_H
#define BRAINSURFACETREEITEM_H

//*************************************************************************************************************
//=============================================================================================================
// INCLUDES
//=============================================================================================================

#include "../../disp3DNew_global.h"

#include "../../helpers/abstracttreeitem.h"
#include "braintreeitem.h"

#include "../../helpers/types.h"
#include "../../helpers/renderable3Dentity.h"

#include "fs/label.h"

#include <disp/helpers/colormap.h>

//*************************************************************************************************************
//=============================================================================================================
// Qt INCLUDES
//=============================================================================================================

#include <QList>
#include <QVariant>
#include <QStringList>
#include <QColor>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QTime>


//*************************************************************************************************************
//=============================================================================================================
// Eigen INCLUDES
//=============================================================================================================

#include <Eigen/Core>


//*************************************************************************************************************
//=============================================================================================================
// DEFINE NAMESPACE DISP3DNEWLIB
//=============================================================================================================

namespace DISP3DNEWLIB
{


//*************************************************************************************************************
//=============================================================================================================
// USED NAMESPACES
//=============================================================================================================

using namespace Eigen;
using namespace DISPLIB;


//*************************************************************************************************************
//=============================================================================================================
// FORWARD DECLARATIONS
//=============================================================================================================


//=============================================================================================================
/**
* BrainSurfaceTreeItem provides a generic brain tree item to hold of brain data (hemi, vertices, tris, etc.) from different sources (FreeSurfer, etc.).
*
* @brief Provides a generic brain tree item.
*/
class DISP3DNEWSHARED_EXPORT BrainSurfaceTreeItem : public AbstractTreeItem
{
    Q_OBJECT;

public:
    typedef QSharedPointer<BrainSurfaceTreeItem> SPtr;             /**< Shared pointer type for BrainSurfaceTreeItem class. */
    typedef QSharedPointer<const BrainSurfaceTreeItem> ConstSPtr;  /**< Const shared pointer type for BrainSurfaceTreeItem class. */

    //=========================================================================================================
    /**
    * Default constructor.
    */
    explicit BrainSurfaceTreeItem(const int& iType = BrainTreeModelItemTypes::UnknownItem, const QString& text = "Surface");

    //=========================================================================================================
    /**
    * Default destructor
    */
    ~BrainSurfaceTreeItem();

    //=========================================================================================================
    /**
    * AbstractTreeItem functions
    */
    QVariant data(int role = Qt::UserRole + 1) const;
    void  setData(const QVariant& value, int role = Qt::UserRole + 1);

    //=========================================================================================================
    /**
    * Adds FreeSurfer data based on surfaces and annotation SETS to this model.
    *
    * @param[in] tSurface           FreeSurfer surface.
    *
    * @return                       Returns true if successful.
    */
    bool addData(const Surface& tSurface, Qt3DCore::QEntity* parent);

    void updateVertColor();

    void updateRtVertColor(const VectorXd &sourceSamples, const VectorXi &vertexIndex, const QString &sColorMapType);

private:
    MatrixX3f createCurvatureVertColor(const VectorXf& curvature, const QColor& colSulci = QColor(50,50,50), const QColor& colGyri = QColor(125,125,125));

    Renderable3DEntity*     m_pRenderable3DEntity;

    BrainTreeItem*          m_pItemSurfColorInfoOrigin; //These are stored as member variables because we do not wat to look for them everytime we call updateVertColor(), especially not whe nwe perform rt source loc
    BrainTreeItem*          m_pItemSurfColSulci;
    BrainTreeItem*          m_pItemSurfColGyri;
};

} //NAMESPACE DISP3DNEWLIB

#endif // BRAINSURFACETREEITEM_H