// Copyright information can be found in the file named COPYING
// located in the root directory of this distribution.

#ifndef _CONSOLETYPES_H_
#define _CONSOLETYPES_H_

#ifndef _DYNAMIC_CONSOLETYPES_H_
#include "console/dynamicTypes.h"
#endif

#ifndef _MATHTYPES_H_
#include "math/mathTypes.h"
#endif

#ifndef _ENGINEPRIMITIVES_H_
#include "console/enginePrimitives.h"
#endif

#ifndef _ENGINESTRUCTS_H_
#include "console/engineStructs.h"
#endif


/// @file
/// Legacy TS-based console type definitions.


/// @ingroup console_system Console System
/// @{

#ifndef Offset
#if defined(TORQUE_COMPILER_GCC) && (__GNUC__ > 3) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1))
#define Offset(m,T) ((int)(&((T *)1)->m) - 1)
#else
#define Offset(x, cls) ((dsize_t)((const char *)&(((cls *)0)->x)-(const char *)0))
#endif
#endif

class GFXShader;
class GFXCubemap;
class CustomMaterial;
class ProjectileData;
class ParticleEmitterData;
class SimPersistID;


// Define Core Console Types
DefineConsoleType( TypeBool, bool )
DefineConsoleType( TypeBoolVector, Vector<bool>)
DefineConsoleType( TypeS8,  S8 )
DefineConsoleType( TypeS32, S32 )
DefineConsoleType( TypeS32Vector, Vector<S32> )
DefineConsoleType( TypeF32, F32 )
DefineConsoleType( TypeF32Vector, Vector<F32> )
DefineUnmappedConsoleType( TypeString, const char * ) // plain UTF-8 strings are not supported in new interop
DefineConsoleType( TypeCaseString, const char * )
DefineConsoleType( TypeRealString, String )
DefineConsoleType( TypeCommand, String )
DefineConsoleType( TypeFilename, const char * )
DefineConsoleType( TypeStringFilename, String )

/// A universally unique identifier.
DefineConsoleType( TypeUUID, Torque::UUID )

/// A persistent ID that is associated with an object.  This type cannot
/// be used to reference PIDs of other objects.
DefineUnmappedConsoleType( TypePID, SimPersistID* );

/// TypeImageFilename is equivalent to TypeStringFilename in its usage,
/// it exists for the benefit of GuiInspector, which will provide a custom
/// InspectorField for this type that can display a texture preview.
DefineConsoleType( TypeImageFilename, String )

/// TypePrefabFilename is equivalent to TypeStringFilename in its usage,
/// it exists for the benefit of GuiInspector, which will provide a 
/// custom InspectorField for this type.
DefineConsoleType( TypePrefabFilename, String )

/// TypeShapeFilename is equivalent to TypeStringFilename in its usage,
/// it exists for the benefit of GuiInspector, which will provide a 
/// custom InspectorField for this type.
DefineConsoleType( TypeShapeFilename, String )

/// TypeMaterialName is equivalent to TypeRealString in its usage,
/// it exists for the benefit of GuiInspector, which will provide a 
/// custom InspectorField for this type.
DefineConsoleType( TypeMaterialName, String )

/// TypeTerrainMaterialIndex is equivalent to TypeS32 in its usage,
/// it exists for the benefit of GuiInspector, which will provide a 
/// custom InspectorField for this type.
DefineConsoleType( TypeTerrainMaterialIndex, S32 )

/// TypeTerrainMaterialName is equivalent to TypeString in its usage,
/// it exists for the benefit of GuiInspector, which will provide a 
/// custom InspectorField for this type.
DefineConsoleType( TypeTerrainMaterialName, const char * )

/// TypeCubemapName is equivalent to TypeRealString in its usage,
/// but the Inspector will provide a drop-down list of CubemapData objects.
DefineConsoleType( TypeCubemapName, String )

DefineConsoleType( TypeParticleParameterString, const char * )

DefineConsoleType( TypeFlag, S32 )
DefineConsoleType( TypeColorI, ColorI )
DefineConsoleType( TypeColorF, ColorF )
DefineConsoleType( TypeSimObjectName, SimObject* )
DefineConsoleType( TypeShader, GFXShader * )

/// A persistent reference to an object.  This reference indirectly goes
/// through the referenced object's persistent ID.
DefineConsoleType( TypeSimPersistId, SimPersistID* )

/// Special field type for SimObject::objectName
DefineConsoleType( TypeName, const char* )

/// TypeRectUV is equivalent to TypeRectF in its usage,
/// it exists for the benefit of GuiInspector, which will provide a 
/// custom InspectorField for this type.
DefineConsoleType( TypeRectUV, RectF )

/// @}

#endif
