// Copyright (C) 2007-2013  CEA/DEN, EDF R&D
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
//
// See http://www.salome-platform.org/ or email : webmaster.salome@opencascade.com
//
// Author : Anthony Geay (CEA/DEN)

#ifndef __PARAMEDMEM_MEDCOUPLING1GTUMESH_HXX__
#define __PARAMEDMEM_MEDCOUPLING1GTUMESH_HXX__

#include "MEDCoupling.hxx"
#include "MEDCouplingPointSet.hxx"
#include "MEDCouplingMemArray.hxx"
#include "MEDCouplingAutoRefCountObjectPtr.hxx"

#include "CellModel.hxx"

namespace ParaMEDMEM
{
  class MEDCoupling1GTUUMeshCellIterator;

  class MEDCoupling1GTUMesh : public MEDCouplingPointSet
  {
  public:
    MEDCOUPLING_EXPORT static MEDCoupling1GTUMesh *New(const char *name, INTERP_KERNEL::NormalizedCellType type);
    MEDCOUPLING_EXPORT static MEDCoupling1GTUMesh *New(const MEDCouplingUMesh *m);
    MEDCOUPLING_EXPORT const INTERP_KERNEL::CellModel& getCellModel() const;
    MEDCOUPLING_EXPORT INTERP_KERNEL::NormalizedCellType getCellModelEnum() const;
    MEDCOUPLING_EXPORT int getMeshDimension() const;
    MEDCOUPLING_EXPORT DataArrayInt *giveCellsWithType(INTERP_KERNEL::NormalizedCellType type) const;
    MEDCOUPLING_EXPORT int getNumberOfCellsWithType(INTERP_KERNEL::NormalizedCellType type) const;
    MEDCOUPLING_EXPORT INTERP_KERNEL::NormalizedCellType getTypeOfCell(int cellId) const;
    MEDCOUPLING_EXPORT std::set<INTERP_KERNEL::NormalizedCellType> getAllGeoTypes() const;
    MEDCOUPLING_EXPORT std::vector<int> getDistributionOfTypes() const;
    MEDCOUPLING_EXPORT void splitProfilePerType(const DataArrayInt *profile, std::vector<int>& code, std::vector<DataArrayInt *>& idsInPflPerType, std::vector<DataArrayInt *>& idsPerType) const;
    MEDCOUPLING_EXPORT DataArrayInt *checkTypeConsistencyAndContig(const std::vector<int>& code, const std::vector<const DataArrayInt *>& idsPerType) const;
    MEDCOUPLING_EXPORT void writeVTKLL(std::ostream& ofs, const std::string& cellData, const std::string& pointData, DataArrayByte *byteData) const;
    MEDCOUPLING_EXPORT std::string getVTKDataSetType() const;
    //
    MEDCOUPLING_EXPORT std::size_t getHeapMemorySizeWithoutChildren() const;
    MEDCOUPLING_EXPORT int getNodalConnectivityLength() const;
    MEDCOUPLING_EXPORT bool isEqualIfNotWhy(const MEDCouplingMesh *other, double prec, std::string& reason) const;
    MEDCOUPLING_EXPORT bool isEqualWithoutConsideringStr(const MEDCouplingMesh *other, double prec) const;
    MEDCOUPLING_EXPORT void checkCoherency() const;
    MEDCOUPLING_EXPORT DataArrayDouble *getBarycenterAndOwner() const;
    MEDCOUPLING_EXPORT MEDCouplingFieldDouble *getMeasureField(bool isAbs) const;
    MEDCOUPLING_EXPORT MEDCouplingFieldDouble *getMeasureFieldOnNode(bool isAbs) const;
    MEDCOUPLING_EXPORT int getCellContainingPoint(const double *pos, double eps) const;
    MEDCOUPLING_EXPORT MEDCouplingFieldDouble *buildOrthogonalField() const;
    MEDCOUPLING_EXPORT DataArrayInt *getCellsInBoundingBox(const double *bbox, double eps) const;
    MEDCOUPLING_EXPORT DataArrayInt *getCellsInBoundingBox(const INTERP_KERNEL::DirectedBoundingBox& bbox, double eps);
    MEDCOUPLING_EXPORT MEDCouplingPointSet *buildFacePartOfMySelfNode(const int *start, const int *end, bool fullyIn) const;
    MEDCOUPLING_EXPORT DataArrayInt *findBoundaryNodes() const;
    MEDCOUPLING_EXPORT MEDCouplingPointSet *buildBoundaryMesh(bool keepCoords) const;
    MEDCOUPLING_EXPORT void findCommonCells(int compType, int startCellId, DataArrayInt *& commonCellsArr, DataArrayInt *& commonCellsIArr) const;
    MEDCOUPLING_EXPORT static MEDCouplingUMesh *AggregateOnSameCoordsToUMesh(const std::vector< const MEDCoupling1GTUMesh *>& parts);
  public:
    MEDCOUPLING_EXPORT virtual void allocateCells(int nbOfCells=0) = 0;
    MEDCOUPLING_EXPORT virtual void insertNextCell(const int *nodalConnOfCellBg, const int *nodalConnOfCellEnd) = 0;
    MEDCOUPLING_EXPORT virtual DataArrayInt *getNodalConnectivity() const = 0;
    MEDCOUPLING_EXPORT virtual void checkCoherencyOfConnectivity() const = 0;
  protected:
    MEDCoupling1GTUMesh(const char *name, const INTERP_KERNEL::CellModel& cm);
    MEDCoupling1GTUMesh(const MEDCoupling1GTUMesh& other, bool recDeepCpy);
    MEDCoupling1GTUMesh();
  protected:
    const INTERP_KERNEL::CellModel *_cm;
  };

  class MEDCoupling1DGTUMesh;

  class MEDCoupling1SGTUMesh : public MEDCoupling1GTUMesh
  {
  public:
    MEDCOUPLING_EXPORT static MEDCoupling1SGTUMesh *New(const char *name, INTERP_KERNEL::NormalizedCellType type);
    MEDCOUPLING_EXPORT static MEDCoupling1SGTUMesh *New(const MEDCouplingUMesh *m);
    //! useless constructor only for CORBA -> not swigged
    MEDCOUPLING_EXPORT static MEDCoupling1SGTUMesh *New();
    MEDCOUPLING_EXPORT MEDCoupling1SGTUMesh *clone(bool recDeepCpy) const;
    MEDCOUPLING_EXPORT MEDCouplingPointSet *deepCpyConnectivityOnly() const;
    // overload of TimeLabel and RefCountObject
    MEDCOUPLING_EXPORT void updateTime() const;
    MEDCOUPLING_EXPORT std::size_t getHeapMemorySizeWithoutChildren() const;
    MEDCOUPLING_EXPORT std::vector<const BigMemoryObject *> getDirectChildren() const;
    // overload of MEDCouplingMesh
    MEDCOUPLING_EXPORT MEDCouplingMeshType getType() const { return SINGLE_STATIC_GEO_TYPE_UNSTRUCTURED; }
    MEDCOUPLING_EXPORT MEDCouplingMesh *deepCpy() const;
    MEDCOUPLING_EXPORT bool isEqualIfNotWhy(const MEDCouplingMesh *other, double prec, std::string& reason) const;
    MEDCOUPLING_EXPORT bool isEqualWithoutConsideringStr(const MEDCouplingMesh *other, double prec) const;
    MEDCOUPLING_EXPORT void checkFastEquivalWith(const MEDCouplingMesh *other, double prec) const;
    MEDCOUPLING_EXPORT void checkCoherency() const;
    MEDCOUPLING_EXPORT void checkCoherency1(double eps=1e-12) const;
    MEDCOUPLING_EXPORT void checkCoherency2(double eps=1e-12) const;
    MEDCOUPLING_EXPORT int getNumberOfCells() const;
    MEDCOUPLING_EXPORT DataArrayInt *computeNbOfNodesPerCell() const;
    MEDCOUPLING_EXPORT DataArrayInt *computeNbOfFacesPerCell() const;
    MEDCOUPLING_EXPORT DataArrayInt *computeEffectiveNbOfNodesPerCell() const;
    MEDCOUPLING_EXPORT void getNodeIdsOfCell(int cellId, std::vector<int>& conn) const;
    MEDCOUPLING_EXPORT std::string simpleRepr() const;
    MEDCOUPLING_EXPORT std::string advancedRepr() const;
    MEDCOUPLING_EXPORT DataArrayDouble *computeIsoBarycenterOfNodesPerCell() const;
    MEDCOUPLING_EXPORT void renumberCells(const int *old2NewBg, bool check=true);
    MEDCOUPLING_EXPORT MEDCouplingMesh *mergeMyselfWith(const MEDCouplingMesh *other) const;
    MEDCOUPLING_EXPORT MEDCouplingUMesh *buildUnstructured() const;
    MEDCOUPLING_EXPORT DataArrayInt *simplexize(int policy);
    MEDCOUPLING_EXPORT void reprQuickOverview(std::ostream& stream) const;
    // overload of MEDCouplingPointSet
    MEDCOUPLING_EXPORT void shallowCopyConnectivityFrom(const MEDCouplingPointSet *other);
    MEDCOUPLING_EXPORT MEDCouplingPointSet *mergeMyselfWithOnSameCoords(const MEDCouplingPointSet *other) const;
    MEDCOUPLING_EXPORT MEDCouplingPointSet *buildPartOfMySelfKeepCoords(const int *begin, const int *end) const;
    MEDCOUPLING_EXPORT MEDCouplingPointSet *buildPartOfMySelfKeepCoords2(int start, int end, int step) const;
    MEDCOUPLING_EXPORT void computeNodeIdsAlg(std::vector<bool>& nodeIdsInUse) const;
    MEDCOUPLING_EXPORT void getReverseNodalConnectivity(DataArrayInt *revNodal, DataArrayInt *revNodalIndx) const;
    MEDCOUPLING_EXPORT void checkFullyDefined() const;
    MEDCOUPLING_EXPORT bool isEmptyMesh(const std::vector<int>& tinyInfo) const;
    MEDCOUPLING_EXPORT DataArrayInt *getNodeIdsInUse(int& nbrOfNodesInUse) const;
    MEDCOUPLING_EXPORT void renumberNodesInConn(const int *newNodeNumbersO2N);
    MEDCOUPLING_EXPORT void fillCellIdsToKeepFromNodeIds(const int *begin, const int *end, bool fullyIn, DataArrayInt *&cellIdsKeptArr) const;
    MEDCOUPLING_EXPORT int getNumberOfNodesInCell(int cellId) const;
    MEDCOUPLING_EXPORT DataArrayDouble *getBoundingBoxForBBTree(double arcDetEps=1e-12) const;
    // overload of MEDCoupling1GTUMesh
    MEDCOUPLING_EXPORT void checkCoherencyOfConnectivity() const;
    MEDCOUPLING_EXPORT void allocateCells(int nbOfCells=0);
    MEDCOUPLING_EXPORT void insertNextCell(const int *nodalConnOfCellBg, const int *nodalConnOfCellEnd);
  public://specific
    MEDCOUPLING_EXPORT void setNodalConnectivity(DataArrayInt *nodalConn);
    MEDCOUPLING_EXPORT DataArrayInt *getNodalConnectivity() const;
    MEDCOUPLING_EXPORT int getNumberOfNodesPerCell() const;
    MEDCOUPLING_EXPORT static MEDCoupling1SGTUMesh *Merge1SGTUMeshes(const MEDCoupling1SGTUMesh *mesh1, const MEDCoupling1SGTUMesh *mesh2);
    MEDCOUPLING_EXPORT static MEDCoupling1SGTUMesh *Merge1SGTUMeshes(std::vector<const MEDCoupling1SGTUMesh *>& a);
    MEDCOUPLING_EXPORT static MEDCoupling1SGTUMesh *Merge1SGTUMeshesOnSameCoords(std::vector<const MEDCoupling1SGTUMesh *>& a);
    MEDCOUPLING_EXPORT MEDCoupling1SGTUMesh *buildSetInstanceFromThis(int spaceDim) const;
    MEDCOUPLING_EXPORT MEDCoupling1GTUMesh *computeDualMesh() const;
    MEDCOUPLING_EXPORT DataArrayInt *sortHexa8EachOther();
    MEDCOUPLING_EXPORT MEDCoupling1SGTUMesh *explodeEachHexa8To6Quad4() const;
  public://serialization
    MEDCOUPLING_EXPORT void getTinySerializationInformation(std::vector<double>& tinyInfoD, std::vector<int>& tinyInfo, std::vector<std::string>& littleStrings) const;
    MEDCOUPLING_EXPORT void resizeForUnserialization(const std::vector<int>& tinyInfo, DataArrayInt *a1, DataArrayDouble *a2, std::vector<std::string>& littleStrings) const;
    MEDCOUPLING_EXPORT void serialize(DataArrayInt *&a1, DataArrayDouble *&a2) const;
    MEDCOUPLING_EXPORT void unserialization(const std::vector<double>& tinyInfoD, const std::vector<int>& tinyInfo, const DataArrayInt *a1, DataArrayDouble *a2,
                                            const std::vector<std::string>& littleStrings);
  private:
    MEDCoupling1SGTUMesh(const char *name, const INTERP_KERNEL::CellModel& cm);
    MEDCoupling1SGTUMesh(const MEDCoupling1SGTUMesh& other, bool recDeepCpy);
    MEDCoupling1SGTUMesh();
  private:
    void checkNonDynamicGeoType() const;
    static MEDCoupling1SGTUMesh *Merge1SGTUMeshesLL(std::vector<const MEDCoupling1SGTUMesh *>& a);
    DataArrayInt *simplexizePol0();
    DataArrayInt *simplexizePol1();
    DataArrayInt *simplexizePlanarFace5();
    DataArrayInt *simplexizePlanarFace6();
    MEDCoupling1DGTUMesh *computeDualMesh3D() const;
    MEDCoupling1DGTUMesh *computeDualMesh2D() const;
  private:
    MEDCouplingAutoRefCountObjectPtr<DataArrayInt> _conn;
  public:
    static const int HEXA8_FACE_PAIRS[6];
  };

  class MEDCoupling1DGTUMesh : public MEDCoupling1GTUMesh
  {
  public:
    MEDCOUPLING_EXPORT static MEDCoupling1DGTUMesh *New(const char *name, INTERP_KERNEL::NormalizedCellType type);
    MEDCOUPLING_EXPORT static MEDCoupling1DGTUMesh *New(const MEDCouplingUMesh *m);
    //! useless constructor only for CORBA -> not swigged
    MEDCOUPLING_EXPORT static MEDCoupling1DGTUMesh *New();
    MEDCOUPLING_EXPORT MEDCoupling1DGTUMesh *clone(bool recDeepCpy) const;
    MEDCOUPLING_EXPORT MEDCouplingPointSet *deepCpyConnectivityOnly() const;
    // overload of TimeLabel and RefCountObject
    MEDCOUPLING_EXPORT void updateTime() const;
    MEDCOUPLING_EXPORT std::size_t getHeapMemorySizeWithoutChildren() const;
    MEDCOUPLING_EXPORT std::vector<const BigMemoryObject *> getDirectChildren() const;
    // overload of MEDCouplingMesh
    MEDCOUPLING_EXPORT MEDCouplingMeshType getType() const { return SINGLE_DYNAMIC_GEO_TYPE_UNSTRUCTURED; }
    MEDCOUPLING_EXPORT MEDCouplingMesh *deepCpy() const;
    MEDCOUPLING_EXPORT bool isEqualIfNotWhy(const MEDCouplingMesh *other, double prec, std::string& reason) const;
    MEDCOUPLING_EXPORT bool isEqualWithoutConsideringStr(const MEDCouplingMesh *other, double prec) const;
    MEDCOUPLING_EXPORT void checkFastEquivalWith(const MEDCouplingMesh *other, double prec) const;
    MEDCOUPLING_EXPORT void checkCoherency() const;
    MEDCOUPLING_EXPORT void checkCoherency1(double eps=1e-12) const;
    MEDCOUPLING_EXPORT void checkCoherency2(double eps=1e-12) const;
    MEDCOUPLING_EXPORT int getNumberOfCells() const;
    MEDCOUPLING_EXPORT DataArrayInt *computeNbOfNodesPerCell() const;
    MEDCOUPLING_EXPORT DataArrayInt *computeNbOfFacesPerCell() const;
    MEDCOUPLING_EXPORT DataArrayInt *computeEffectiveNbOfNodesPerCell() const;
    MEDCOUPLING_EXPORT void getNodeIdsOfCell(int cellId, std::vector<int>& conn) const;
    MEDCOUPLING_EXPORT std::string simpleRepr() const;
    MEDCOUPLING_EXPORT std::string advancedRepr() const;
    MEDCOUPLING_EXPORT DataArrayDouble *computeIsoBarycenterOfNodesPerCell() const;
    MEDCOUPLING_EXPORT void renumberCells(const int *old2NewBg, bool check=true);
    MEDCOUPLING_EXPORT MEDCouplingMesh *mergeMyselfWith(const MEDCouplingMesh *other) const;
    MEDCOUPLING_EXPORT MEDCouplingUMesh *buildUnstructured() const;
    MEDCOUPLING_EXPORT DataArrayInt *simplexize(int policy);
    MEDCOUPLING_EXPORT void reprQuickOverview(std::ostream& stream) const;
    // overload of MEDCouplingPointSet
    MEDCOUPLING_EXPORT void shallowCopyConnectivityFrom(const MEDCouplingPointSet *other);
    MEDCOUPLING_EXPORT MEDCouplingPointSet *mergeMyselfWithOnSameCoords(const MEDCouplingPointSet *other) const;
    MEDCOUPLING_EXPORT MEDCouplingPointSet *buildPartOfMySelfKeepCoords(const int *begin, const int *end) const;
    MEDCOUPLING_EXPORT MEDCouplingPointSet *buildPartOfMySelfKeepCoords2(int start, int end, int step) const;
    MEDCOUPLING_EXPORT void computeNodeIdsAlg(std::vector<bool>& nodeIdsInUse) const;
    MEDCOUPLING_EXPORT void getReverseNodalConnectivity(DataArrayInt *revNodal, DataArrayInt *revNodalIndx) const;
    MEDCOUPLING_EXPORT void checkFullyDefined() const;
    MEDCOUPLING_EXPORT bool isEmptyMesh(const std::vector<int>& tinyInfo) const;
    MEDCOUPLING_EXPORT DataArrayInt *getNodeIdsInUse(int& nbrOfNodesInUse) const;
    MEDCOUPLING_EXPORT void renumberNodesInConn(const int *newNodeNumbersO2N);
    MEDCOUPLING_EXPORT void fillCellIdsToKeepFromNodeIds(const int *begin, const int *end, bool fullyIn, DataArrayInt *&cellIdsKeptArr) const;
    MEDCOUPLING_EXPORT int getNumberOfNodesInCell(int cellId) const;
    MEDCOUPLING_EXPORT DataArrayDouble *getBoundingBoxForBBTree(double arcDetEps=1e-12) const;
    // overload of MEDCoupling1GTUMesh
    MEDCOUPLING_EXPORT void checkCoherencyOfConnectivity() const;
    MEDCOUPLING_EXPORT void allocateCells(int nbOfCells=0);
    MEDCOUPLING_EXPORT void insertNextCell(const int *nodalConnOfCellBg, const int *nodalConnOfCellEnd);
  public://specific
    MEDCOUPLING_EXPORT void setNodalConnectivity(DataArrayInt *nodalConn, DataArrayInt *nodalConnIndex);
    MEDCOUPLING_EXPORT DataArrayInt *getNodalConnectivity() const;
    MEDCOUPLING_EXPORT DataArrayInt *getNodalConnectivityIndex() const;
    MEDCOUPLING_EXPORT MEDCoupling1DGTUMesh *copyWithNodalConnectivityPacked(bool& isShallowCpyOfNodalConnn) const;
    MEDCOUPLING_EXPORT bool retrievePackedNodalConnectivity(DataArrayInt *&nodalConn, DataArrayInt *&nodalConnIndx) const;
    MEDCOUPLING_EXPORT bool isPacked() const;
    MEDCOUPLING_EXPORT static MEDCoupling1DGTUMesh *Merge1DGTUMeshes(const MEDCoupling1DGTUMesh *mesh1, const MEDCoupling1DGTUMesh *mesh2);
    MEDCOUPLING_EXPORT static MEDCoupling1DGTUMesh *Merge1DGTUMeshes(std::vector<const MEDCoupling1DGTUMesh *>& a);
    MEDCOUPLING_EXPORT static MEDCoupling1DGTUMesh *Merge1DGTUMeshesOnSameCoords(std::vector<const MEDCoupling1DGTUMesh *>& a);
    MEDCOUPLING_EXPORT static DataArrayInt *AggregateNodalConnAndShiftNodeIds(const std::vector<const DataArrayInt *>& nodalConns, const std::vector<int>& offsetInNodeIdsPerElt);
    MEDCOUPLING_EXPORT static std::vector<int> BuildAPolygonFromParts(const std::vector< std::vector<int> >& parts);
    MEDCOUPLING_EXPORT MEDCoupling1DGTUMesh *buildSetInstanceFromThis(int spaceDim) const;
  public://serialization
    MEDCOUPLING_EXPORT void getTinySerializationInformation(std::vector<double>& tinyInfoD, std::vector<int>& tinyInfo, std::vector<std::string>& littleStrings) const;
    MEDCOUPLING_EXPORT void resizeForUnserialization(const std::vector<int>& tinyInfo, DataArrayInt *a1, DataArrayDouble *a2, std::vector<std::string>& littleStrings) const;
    MEDCOUPLING_EXPORT void serialize(DataArrayInt *&a1, DataArrayDouble *&a2) const;
    MEDCOUPLING_EXPORT void unserialization(const std::vector<double>& tinyInfoD, const std::vector<int>& tinyInfo, const DataArrayInt *a1, DataArrayDouble *a2,
                                            const std::vector<std::string>& littleStrings);
  private:
    MEDCoupling1DGTUMesh(const char *name, const INTERP_KERNEL::CellModel& cm);
    MEDCoupling1DGTUMesh(const MEDCoupling1DGTUMesh& other, bool recDeepCpy);
    MEDCoupling1DGTUMesh();
  private:
    void checkDynamicGeoT2ype() const;
    static MEDCoupling1DGTUMesh *Merge1DGTUMeshesLL(std::vector<const MEDCoupling1DGTUMesh *>& a);
  private:
    MEDCouplingAutoRefCountObjectPtr<DataArrayInt> _conn_indx;
    MEDCouplingAutoRefCountObjectPtr<DataArrayInt> _conn;
  };
}

#endif
