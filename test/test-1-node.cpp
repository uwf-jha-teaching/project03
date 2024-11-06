#include "../node.hpp"
#include "catch/catch.hpp"

TEST_CASE("Node") {
  Node n("root", 'd');
  CHECK("root" == n.getName());
  CHECK('d' == n.getType());
  CHECK(nullptr == n.getParent());
  CHECK(0 == n.getChildren().size());

  Node* child = new Node("child", 'f');
  n.addChild(child);
  CHECK(child == n.getChild("child"));
  CHECK((&n == child->getParent()));

  n.addChild("second", 'f');
  CHECK('f' == n.getChild("second")->getType());

  Node* parent = new Node("parent", 'd');
  n.setParent(parent);
  CHECK(parent == n.getParent());

  CHECK(2 == n.getChildren().size());

  /* Verify removal of child and all successors */
  n.getChild("second")->addChild("seconds-new-baby", 'f');  // add grandchild
  n.removeChild("second");  // should remove second and seconds-new-baby
  CHECK(1 == n.getChildren().size());

  delete child;
  delete parent;
}
