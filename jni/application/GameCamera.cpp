#include "GameCamera.h"

Thing * GameCamera::focus = NULL;
float GameCamera::relativeSize = 0.2;
float GameCamera::targetZoom = 0.2;
float GameCamera::offset = 0.4;
float GameCamera::targetOffset = 0.4;
Point2f GameCamera::location = Point2f();

void GameCamera::setFocus(Thing * object) {
  focus = object;
}

void GameCamera::setZoomOutView() {
  targetZoom = 0.25;
}

void GameCamera::set46View() {
  targetOffset = 0.4;
}

pair<Point2f, Point2f> GameCamera::getView() {
  Point2f center = getCenter();
  Vector2f viewSize = Vector2f(focus->getSize().y/relativeSize*1.6f, 
                               focus->getSize().y/relativeSize);
  Point2f topLeft = Point2f(center.x - (viewSize*offset).x, 
                            center.y - viewSize.y + focus->getSize().y/relativeSize*0.1);
  Point2f bottomRight = Point2f(center.x + (viewSize*(1-offset)).x, 
                                center.y + focus->getSize().y/relativeSize*0.1);
  return make_pair(topLeft, bottomRight);
}

void GameCamera::pan() {
  location = location.interpolate_to(0.2, focus->getPos());
  if (targetZoom > relativeSize) { // zoom in
    relativeSize = relativeSize*0.95 + targetZoom*0.05;
    offset = offset*0.95 + targetOffset*0.05;
  } else { // zooming out
    relativeSize = relativeSize*0.98 + targetZoom*0.02;
    offset = offset*0.98 + targetOffset*0.02;
  }
}

Point2f GameCamera::getCenter() {
  return location;
}
    
void GameCamera::renderThing(Thing * thing) {
  float depthVerticalOffset = (thing->getDepth()-1)*100;
  Point2f parallax = Point2f((thing->getPos().x-getCenter().x)*thing->getDepth()+getCenter().x, (thing->getPos().y-getCenter().y+depthVerticalOffset)*thing->getDepth()+getCenter().y);
  
  thing->render(parallax, thing->getSize()*thing->getDepth());
}
