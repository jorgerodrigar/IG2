#include "Sinbad.h"

Sinbad::Sinbad(Ogre::SceneNode* sceneNode, std::string mesh, float duracion, float tamDesp) : GameObject(sceneNode, mesh) {
	sceneNode_->setPosition(400, 100, -300);                              // cambiamos posicion y escala del nodo mSinbadNode respecto a su padre,
	sceneNode_->setScale(20, 20, 20);                                     // el nodo mPlano

	espada1 = sceneNode_->getCreator()->createEntity("Sword.mesh");  // creamos dos espadas y las situamos
	espada2 = sceneNode_->getCreator()->createEntity("Sword.mesh");
	ent->attachObjectToBone("Sheath.R", espada1);                    // en sus fundas
	ent->attachObjectToBone("Sheath.L", espada2);
	animations.resize(4);
	animations[0] = ent->getAnimationState("Dance");
	animations[1] = ent->getAnimationState("RunBase");
	animations[2] = ent->getAnimationState("RunTop");

	Animation* animation = sceneNode_->getCreator()->createAnimation("recorrePlano", duracion);
	NodeAnimationTrack* track = animation->createNodeTrack(0);
	track->setAssociatedNode(sceneNode_);
	Vector3 keyframePos = { 0, 0, 0 };
	Real longitudPaso = duracion / 4.0; // uniformes
	TransformKeyFrame * kf; // 5 keyFrames: origen(0), arriba, origen, abajo, origen(4)

	kf = track->createNodeKeyFrame(longitudPaso * 0); // Keyframe 0: origen
	kf->setTranslate(keyframePos); // Origen: Vector3


	kf = track->createNodeKeyFrame(longitudPaso * 1); // Keyframe 1: arriba
	keyframePos += Ogre::Vector3::UNIT_Y * tamDesp;
	kf->setTranslate(keyframePos); // Arriba


	kf = track->createNodeKeyFrame(longitudPaso * 2); // Keyframe 2: origen
	keyframePos += Ogre::Vector3::NEGATIVE_UNIT_Y * tamDesp;
	kf->setTranslate(keyframePos); // Origen

	kf = track->createNodeKeyFrame(longitudPaso * 3); // Keyframe 3: abajo
	keyframePos += Ogre::Vector3::NEGATIVE_UNIT_Y * tamDesp;
	kf->setTranslate(keyframePos); // Abajo

	kf = track->createNodeKeyFrame(longitudPaso * 4); // Keyframe 4: origen
	keyframePos += Ogre::Vector3::UNIT_Y * tamDesp;
	kf->setTranslate(keyframePos); // Origen

	sceneNode_->setInitialState();

	animations[3] = sceneNode_->getCreator()->createAnimationState("recorrePlano");

	updateAnim();
}

void Sinbad::setAnimation(string name, bool b) {         // cambia de animacion, la activa y hace que se repita
	for (int i = 0; i < animations.size(); i++) {
		if (animations[i]->getAnimationName() == name) {
			animations[i]->setEnabled(b);
			animations[i]->setLoop(b);
		}
	}
};

bool Sinbad::keyPressed(const OgreBites::KeyboardEvent& evt) {
	if (evt.keysym.sym == SDLK_r) {           // si pulsamos "r" pasara de bailar a correr y viceversa
		if (actualAnim == DANCING) 	actualAnim = RUNNING;
		else actualAnim = DANCING;
		updateAnim();
	}
	return true;
}

void Sinbad::updateAnim() {
	if (actualAnim == RUNNING) {
		setAnimation("RunBase", true);
		setAnimation("RunTop", true);
		setAnimation("recorrePlano", true);
		setAnimation("Dance", false);
		ent->detachObjectFromBone(espada1);
		ent->attachObjectToBone("Handle.R", espada1);
	}
	else if (actualAnim == DANCING) {
		setAnimation("RunBase", false);
		setAnimation("RunTop", false);
		setAnimation("recorrePlano", false);
		setAnimation("Dance", true);
		ent->detachObjectFromBone(espada1);
		ent->attachObjectToBone("Sheath.R", espada1);
	}
}