#include <ros/ros.h>
#include <ros/console.h>
#include <nav_msgs/Path.h>
#include <std_msgs/String.h>
#include <geometry_msgs/Quaternion.h>
#include <geometry_msgs/PoseStamped.h>
#include <tf/transform_broadcaster.h>
#include <tf/tf.h>
#include <qptrajectory.h>

geometry_msgs::Point pos;
double count = 0;
double max;
double sample = 0.02;
qptrajectory plan;
trajectory_profile p1, p2, p3, p4, p5, p6, p7, p8, p9;
std::vector<trajectory_profile> data;

void traj_plan()
{
	p1.pos << 0.0,  0.0, 2.5;
	p1.vel << 0.0,  0.0, 0.0;
	p1.acc << 0.0, -0.0, 0.0;

	p2.pos << 5.0,  3.0, 2.5;
	p2.vel << 0.0,  0.0, 0.0;
	p2.acc << 0.0, -0.0, 0.0;

	p3.pos << 0.0, 8.0, 2.5;
	p3.vel << 0.0, 0.0, 0.0;
	p3.acc << 0.0, 0.0, 0.0;

	p4.pos << -5.0, 3.0, 2.5;
	p4.vel <<  0.0, 0.0, 0.0;
	p4.acc <<  0.0, 0.0, 0.0;

	p5.pos << 0.0, 0.0, 2.5;
	p5.vel << 0.0, 0.0, 0.0;
	p5.acc << 0.0, 0.0, 0.0;

	p6.pos << 5.0, -3.0, 2.5;
	p6.vel << 0.0,  0.0, 0.0;
	p6.acc << 0.0,  0.0, 0.0;

	p7.pos << 0.0, -8.0, 2.5;
	p7.vel << 0.0,  0.0, 0.0;
	p7.acc << 0.0,  0.0, 0.0;

	p8.pos << -5.0, -3.0, 2.5;
	p8.vel <<  0.0,  0.0, 0.0;
	p8.acc <<  0.0,  0.0, 0.0;

	p9.pos << 0.0, 0.0, 2.5;
	p9.vel << 0.0, 0.0, 0.0;
	p9.acc << 0.0, 0.0, 0.0;

	path_def path;
	path.push_back(segments(p1, p2, 3));
	path.push_back(segments(p2, p3, 2));
	path.push_back(segments(p3, p4, 2));
	path.push_back(segments(p4, p5, 2));
	path.push_back(segments(p5, p6, 2));
	path.push_back(segments(p6, p7, 2));
	path.push_back(segments(p7, p8, 3));
	path.push_back(segments(p8, p9, 3));

	data = plan.get_profile(path, path.size(), sample);
	max = data.size();
}

main (int argc, char **argv)
{
	ros::init (argc, argv, "showpath");
	ros::NodeHandle ph;
	ros::Publisher path_pub = ph.advertise<nav_msgs::Path>("trajectory", 1, true);
	ros::Rate loop_rate(100);
	ros::Time current_time, last_time;
	current_time = ros::Time::now();
	last_time = ros::Time::now();
	
	nav_msgs::Path path;
	path.header.stamp = current_time;
	path.header.frame_id = "map";

	traj_plan();

	while (ros::ok()) {

		if(count >= max) {
			pos.x = 0;
			pos.y = 0;
			pos.z = 2.5;
		} else {
			pos.x = data[count].pos[0];
			pos.y = data[count].pos[1];
			pos.z = 2.5;
		}
		count++;

		geometry_msgs::PoseStamped this_pose_stamped;
		this_pose_stamped.pose.position.x = pos.x;
		this_pose_stamped.pose.position.y = pos.y;
		this_pose_stamped.pose.position.z = pos.z;

		this_pose_stamped.header.stamp = current_time;
		this_pose_stamped.header.frame_id = "map";
		path.poses.push_back(this_pose_stamped);

		path_pub.publish(path);
		ros::spinOnce();

		last_time = current_time;
		loop_rate.sleep();
	}
	return 0;
}
