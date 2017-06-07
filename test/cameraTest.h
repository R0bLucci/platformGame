#include <gtest/gtest.h>
#include "../src/camera.cpp"
#include "../header/globals.h"

TEST(CameraTest, getters){
	Camera camera(Vector2(0,0), 50, 50, 200, 100);
	EXPECT_EQ(50, camera.getWidth());	
	EXPECT_EQ(50, camera.getHeight());	
}

TEST(CameraTest, move){
	Camera camera(Vector2(), 50, 50, 1980, 1080);
	camera.move(321.0, 257.0);
	EXPECT_EQ(Vector2(1.0, 1.0), camera.getPosition());
}
