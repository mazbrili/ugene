/**
 * UGENE - Integrated Bioinformatics Tools.
 * Copyright (C) 2008-2011 UniPro <ugene@unipro.ru>
 * http://ugene.unipro.ru
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */

#ifndef _U2_BIOSTRUCT3D_H_
#define _U2_BIOSTRUCT3D_H_

#include <U2Core/Vector3D.h>
#include <U2Core/global.h>
#include <U2Core/AnnotationData.h>

#include <QtCore/QString>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QSharedData>
#include <QtCore/QMultiMap>

namespace U2 {

class U2Region;

//! Represents biopolimer residue
class ResidueData : public QSharedData    
{ 
public:
    enum Type {
        TYPE_UNKNOWN, TYPE_PROTEIN, TYPE_DNA, TYPE_RNA
    };
    Type type;
    QByteArray name;
    char acronym;
    int chainIndex;
    ResidueData() : type(TYPE_UNKNOWN), acronym(' '), chainIndex(0) {}
};

typedef QSharedDataPointer<ResidueData> SharedResidue;

//! Represents atom
class AtomData : public QSharedData
{
public:
    int atomicNumber;
    int chainIndex;
    int residueIndex;
    QByteArray name;
    Vector3D coord3d;
    float occupancy, temperature;

public:
    AtomData() {
        chainIndex = 0;
        residueIndex = 0;
        atomicNumber = 0;
        temperature = -1.0;
        occupancy = 0;
    }

};

typedef QSharedDataPointer<AtomData> SharedAtom;

//! Represents chemical bond between atoms
class Bond
{
    SharedAtom atom1;
    SharedAtom atom2;
public:
    Bond(const SharedAtom& a1, const SharedAtom& a2) : atom1(a1), atom2(a2) { }
    const SharedAtom getAtom1() { return atom1; }
    const SharedAtom getAtom2() { return atom2; }
};

//! Represents protein secondary structure: alpha-helix, beta-strand, turn
class SecondaryStructure : public QSharedData {
public:
    enum Type {
        Type_None = -1, Type_AlphaHelix, Type_PiHelix, Type_310Helix,
        Type_BetaStrand, Type_BetaBridge, Type_Turn, Type_BendRegion
    };

    Type type;
    char chainIdentifier;
    int chainIndex;
    int startSequenceNumber;
    int endSequenceNumber;

public:
    SecondaryStructure() : type(Type_None)
    {
        startSequenceNumber = 0;
        endSequenceNumber = 0;
        chainIndex = 0;
        chainIdentifier = 0;
    }
};

typedef QSharedDataPointer<SecondaryStructure> SharedSecondaryStructure;

//! Model 3D
/*!
    Represents collection of molecule atomic coordinates and bonds
*/
class Molecule3DModel
{
public:
    QList<SharedAtom> atoms;
    QList<Bond> bonds;
};

//! Molecule
/*!
    Represents molecule chain (biopolymer or any other)
*/
class MoleculeData : public QSharedData {
public:
    MoleculeData(): engineered(false)  {}
    MoleculeData(const QString& molName) : name(molName), engineered(false) {}
    QMap<int, SharedResidue> residueMap;

    // this list used by biostrct renderers
    // its indexes differ(sic!) from modelIds in QMap <int, AtomCoordSet> BioStruct3D::modelMap;
    // but length, order of map and list believed to be equal
    QList<Molecule3DModel> models;

    QList<SharedAnnotationData> annotations;
    QString name;
    bool engineered;
};

typedef QSharedDataPointer<MoleculeData> SharedMolecule;
typedef QHash<int, SharedAtom> AtomCoordSet; 

//! Biological 3D structure
class U2CORE_EXPORT BioStruct3D {
public:
    static QString SecStructAnnotationTag;
    static QString MoleculeAnnotationTag;
    static QString AlphaHelixAnnotationTag;
    static QString BetaStrandAnnotationTag;
    static QString TurnAnnotationTag;
    static QString ChainIdQualifierName;
    static QString SecStructTypeQualifierName;

public:
    BioStruct3D() {}

    QMap <int, SharedMolecule> moleculeMap;
    QMap <int, AtomCoordSet> modelMap;
    QList<SharedAnnotationData> annotations;
    QList<SharedSecondaryStructure> secondaryStructures;
    QList<Bond> interMolecularBonds;
    QString descr;
    QByteArray pdbId;
    double maxDistFromCenter;
    Vector3D rotationCenter;

    // Const member functions
    Vector3D getCenter() const { return rotationCenter; }
    double getMaxDistFromCenter()  const { return maxDistFromCenter; }
    QByteArray getRawSequenceByChainId(int id) const;
    int getNumberOfAtoms() const;
    int getNumberOfResidues() const;
    const SharedAtom getAtomById(int index, int modelIndex) const;
    const SharedResidue getResidueById(int chainIndex, int residueIndex) const;

    // Modifiers
    void calcCenterAndMaxDistance();
    void generateAnnotations();

public:
    // Static methods
    static const QString getSecStructTypeName(SecondaryStructure::Type type);

private:
    void generateChainAnnotations();
    void generateSecStructureAnnotations();
};

//! Shared data for BioStruct3DSelection
class BioStruct3DSelectionData : public QSharedData {
public:
    BioStruct3DSelectionData() : QSharedData() {}
    BioStruct3DSelectionData(const BioStruct3DSelectionData &other) : QSharedData(), selection(other.selection) {}

    ~BioStruct3DSelectionData() {}

    // <chainId, residueId> presented in map believed to be selected
    // can be optimized on assumption that residue ids are continual
    QMultiMap<int, int> selection;

};  // class BioStruct3DSelectionData

//! Represents part of BioStruct3D.
class U2CORE_EXPORT BioStruct3DSelection {
public:
    BioStruct3DSelection(const BioStruct3D &biostruct);
    BioStruct3DSelection(const BioStruct3DSelection &other);

    const BioStruct3D &getBioStruct3D() const { return biostruct; }

    bool inSelection(int chainId, int residueId) const;
    bool isEmpty() const { return data->selection.isEmpty(); }

    void add(int chain, const U2Region &region);
    void add(int chain, const QVector<U2Region> &regions);

    void remove(int chain, const U2Region &region);
    void remove(int chain, const QVector<U2Region> &regions);

    void update(int chain, const U2Region &add, const U2Region &remove);
    void update(int chain, const QVector<U2Region> &adds, const QVector<U2Region> &removes);

private:
    const BioStruct3D &biostruct;
    QSharedDataPointer<BioStruct3DSelectionData> data;
};  // class U2CORE_EXPORT BioStruct3DSelection

} // namespace U2



#endif // _U2_BIOSTRUCT3D_H_
