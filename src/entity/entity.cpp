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

    _boundingBox = ofRectangle(_position - _size/2, _size, _size);
}

void Entity::update(double deltaTime) {
    _boundingBox.setPosition(_position.x - _size/2, _position.y - _size/2);
}

void Entity::draw() {
    ofDrawBitmapStringHighlight("I should not be here", _position, COLOURS.RED, COLOURS.BACKGROUND);
}

void Entity::drawBoundingBox() {
    ofSetColor(COLOURS.RED);
    ofDrawRectangle(_boundingBox);

    ofSetColor(COLOURS.GREEN);
    ofDrawLine(_position, _position + (_direction * _size));
}

void Entity::setPosition(vec2 position) {
    _position = position;
}

void Entity::setSize(float size) {
    _size = size;
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