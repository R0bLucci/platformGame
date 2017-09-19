#include <gtest/gtest.h>
#include "../src/camera.cpp"
#include "../src/global.cpp"

TEST(CameraTest, getters){
	Camera camera(Vector2<double>(0,0), 50, 50, 200, 100);
	EXPECT_EQ(50, camera.getWidth());	
	EXPECT_EQ(50, camera.getHeight());	
}

TEST(CameraTest, move){
	Camera camera(Vector2<double>(), 50, 50, 1980, 1080);
	camera.move(321.0, 257.0);
	EXPECT_EQ(Vector2<double>(1.0, 1.0), camera.getPosition());
}
