#!/usr/bin/env python

# _T1A
import collections
def tree():
    return collections.defaultdict(tree)

fieldTree = tree()
meshDict = {}
# _T1B

import os
filename = "timeseries.med"
filepath = os.path.join(os.path.abspath(os.path.dirname(__file__)),filename)

# _T2A
from MEDLoader import MEDLoader
meshNames = MEDLoader.GetMeshNames(filepath)

meshDimRelToMax = 0 # 0 = no restriction

for meshName in meshNames:
    mesh = MEDLoader.ReadUMeshFromFile(filepath,meshName,meshDimRelToMax)
    meshDict[meshName] = mesh

    fieldNames = MEDLoader.GetAllFieldNamesOnMesh(filepath,meshName)
    for fieldName in fieldNames:
        listOfTypes = MEDLoader.GetTypesOfField(filepath,meshName,fieldName)
        for typeOfDiscretization in listOfTypes:
            fieldIterations = MEDLoader.GetFieldIterations(typeOfDiscretization,
                                                           filepath,
                                                           meshName,
                                                           fieldName)
            for fieldIteration in fieldIterations:
                itNumber = fieldIteration[0]
                itOrder  = fieldIteration[1]

                field = MEDLoader.ReadField(typeOfDiscretization,
                                            filepath,
                                            meshName,
                                            meshDimRelToMax,
                                            fieldName,
                                            itNumber,
                                            itOrder)

                fieldTree\
                           [meshName]\
                           [fieldName]\
                           [typeOfDiscretization]\
                           [itNumber][itOrder] = field
# _T2B

# Q: use a list of structures whose an attribute could be a
# MEDCoupling field? Or a tree that you cross using attribute and
# whose leaves are the MEDCoupling fields?
# R: I think that the default structure should be a simple list that
# store objects whith properties that corresponds to the metadata (and
# if loaded the MEDCouplingField or Mesh). Then for specific request,
# a BTree could be create to organize the search (for example if we
# request all the fields for a given iteration step, then we should
# use the iteration step as a first classifaction switch of the tree

print fieldTree.keys()

# _T3A
for meshName in fieldTree.keys():
    print "%s"%meshName
    for fieldName in fieldTree[meshName].keys():
        print "  %s"%fieldName
        for fieldType in fieldTree[meshName][fieldName].keys():
            print "    %s"%fieldType
            for itNumber in fieldTree[meshName][fieldName][fieldType].keys():
                for itOrder in fieldTree[meshName][fieldName][fieldType][itNumber].keys():
                    print "      (%s,%s)"%(itNumber,itOrder)
                    print fieldTree[meshName][fieldName][fieldType][itNumber][itOrder]
# _T3B
