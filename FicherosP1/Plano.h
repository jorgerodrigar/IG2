#pragma once
#include "GameObject.h"
#include <OgreCameraMan.h>
#include <OgreMovablePlane.h>
#include <OgreTextureManager.h>
#include <OgreRenderTexture.h>
#include <OgreViewport.h>
#include <OgreHardwarePixelBuffer.h>
#include <OgreSubEntity.h>
#include <OgreMaterial.h>
#include <OgreTechnique.h>
#include <OgrePass.h>

using namespace std;
using namespace Ogre;

class Plano : public GameObject
{
private:
	Ogre::Entity* plano = nullptr;        // entidad plano a la que le a�adimos textura y material
	MovablePlane* mp = nullptr;           // descripcion geometrica/matematica del plano
public:
	Plano(Ogre::SceneNode* sceneNode, string name, Camera* camRef, Vector3 u = Vector3::UNIT_Y, Ogre::Real f = 0, int width = 1080, int height = 800, int numWsegments = 100,
		int numHsegments = 80, bool normals = true, int numTexCoords = 1, float numUtile = 1.0, float numVtile = 1.0, Vector3 v = -Vector3::UNIT_Z);
	void setMaterial(string name) { plano->setMaterialName(name); }
	virtual ~Plano();
};
