#ifndef KEYSBEHAVIOUR_HPP
#define KEYSBEHAVIOUR_HPP

#include "mge/behaviours/AbstractBehaviour.hpp"

/**
 * KeysBehaviour allows you to move an object u
 
 g the keyboard in its own local space.
 * Left right turns, forward back moves.
 */
class KeysBehaviour : public AbstractBehaviour
{
	public:
	    //move speed is in units per second, turnspeed in degrees per second
		KeysBehaviour(float pMoveSpeed = 5, float pTurnSpeed = 45);
		virtual ~KeysBehaviour();
		virtual bool update( float pStep );

    private:
        float _moveSpeed;
        float _turnSpeed;
};

#endif // KEYSBEHAVIOUR_HPP
