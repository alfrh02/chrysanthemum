#include "entity.h"

using namespace glm;

Entity::Entity(vec2 position, vec2 direction, float rotation, float size, unsigned short health, float speed) {
    _position = position;
    _direction = direction;
    _rotation = rotation;

    _size = size;
    _speed = speed;
    _health = health;
    _maxHealth = health;
    _damage = _size / 5;

    _boundingBox = ofRectangle(_position - _size/2, _size, _size);

    _identity = "Entity";
}

void Entity::update(double deltaTime) {
    // for some reason ofRectangle.setPosition() will not take a vec2, but will take x and y individually.
    _boundingBox.setPosition(_position.x - _size/2, _position.y - _size/2);
}

void Entity::draw() {
    ofDrawBitmapStringHighlight("I should not be here", _position, COLORS.RED, COLORS.BACKGROUND);
}

void Entity::drawBoundingBox() {
    ofSetColor(COLORS.RED);
    ofDrawRectangle(_boundingBox);

    // ofDrawBitmapStringHighlight(to_string(_health), _position + vec2(_size/2, 0), COLOURS.RED, COLOURS.FOREGROUND);
    ofDrawBitmapString(to_string(_health), _position + vec2(_size/2, 0));
    // ofDrawBitmapStringHighlight(_identity, _position + vec2(0, 16), COLOURS.RED, COLOURS.FOREGROUND);
    // ofDrawBitmapStringHighlight(to_string(_position.x) + ", " + to_string(_position.y), _position + vec2(0, 32), COLOURS.RED, COLOURS.FOREGROUND);

    ofSetColor(COLORS.GREEN);
    ofDrawLine(_position, _position + (_direction * _size));
}

void Entity::physicsCollision(vec2 colliderPosition, float colliderSpeed, unsigned short damage) {
    _speed = (_speed / 2) + (colliderSpeed / 2);
    _direction = normalize(_position - colliderPosition);
    _health -= damage;
}

void Entity::setPosition(vec2 position) {
    _position = position;
}

void Entity::setDirection(vec2 direction) {
    _direction = direction;
}

void Entity::setSize(float size) {
    _size = size;
}

void Entity::setSpeed(float speed) {
    _speed = speed;
}

void Entity::setHealth(unsigned short health) {
    _health = health;
}

vec2 Entity::getPosition() {
    return _position;
}

vec2 Entity::getDirection() {
    return _direction;
}

float Entity::getRotation() {
    return _rotation;
}

float Entity::getSize() {
    return _size;
}

float Entity::getSpeed() {
    return _speed;
}

short Entity::getHealth() {
    return _health;
}

unsigned short Entity::getDamage() {
    // return _damage;
    return _damage;
}

ofRectangle Entity::getBoundingBox() {
    return _boundingBox;
}

string Entity::getIdentity() {
    return _identity;
}