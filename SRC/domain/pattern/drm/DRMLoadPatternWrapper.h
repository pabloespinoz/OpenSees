/* 
 * @author: gnp <petropoulos@gmail.com>
 *
 * @Description: DRM Load Pattern Wrapper Header File
 *               purpose is to ease the implementation
 *               of the send/recv self methods
 *
 * @Date: 7/7/08
 *
 */


#ifndef DRMLoadPatternWrapper_h
#define DRMLoadPatternWrapper_h

#include <LoadPattern.h>
#include <Domain.h>
#include <LoadPattern.h>
#include "DRMBoundaryLayerDecorator.h"
#include "DRMLoadPattern.h"
#include "DRMInputHandler.h"
#include <Vector.h>
#include <ID.h>
#include <Message.h>
#include <Matrix.h>
#include <Element.h>
#include <map>
#include <set>
#include <Channel.h>
#include <FEM_ObjectBroker.h>
#include <string>
#include <classTags.h>

class DRMLoadPatternWrapper : public LoadPattern
{
  public :
    
    DRMLoadPatternWrapper();
  
    DRMLoadPatternWrapper(int _tag, double _cfact, char** _in_files, int _files,  double _dt,
			  int _num_steps, int* _file_data, int _fileData_size,
			  int __nd1, int __nd2,
			  double* _drm_box_crds, double* _eleD,
			  int _steps_to_cache);

    virtual ~DRMLoadPatternWrapper();

    void initialize();

    void applyLoad(double time);

    int sendSelf(int commitTag, Channel& theChannel); 

    int recvSelf(int commitTag, Channel& theChannel, FEM_ObjectBroker& theBroker); 

    void Print(OPS_Stream &s, int flag);

    LoadPattern* getCopy();
    
 private:

    char** infiles;        // 6 input file names for 5 faces (2 for face 5)
    int files;             // number of input files, 6 (2 for face 5)
    double dt;             // time step
    int num_steps;         // number of time steps
    int *file_data;        // array that contain the number of grids(elements) along edges of each face
    int fileData_size;     // length of array that contain the number of grids(elements) along edges of each face
    int nd1;               // number of grid points on face 5a
    int nd2;               // number of grid points on face 5b
    double *drm_box_crds;  // min and max of x, y, z of the DRM subdomain
    double *eleD;          // mesh size of element along the x, y, z global axis
    int steps_to_cache;    // number of cached steps

    DRMLoadPattern* myPattern;
    
    double factor;
    
    bool initialized;
    bool cleanUpAfterMySelf;
};
#endif

