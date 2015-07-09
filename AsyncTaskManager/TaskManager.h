#pragma once

#include <boost/thread.hpp>
#include <boost/asio.hpp>

#include "Task.h"
#include "TaskEventsBroadcaster.h"

enum TasksExecutionState { NONE, RUNNING, FINISHED, SUSPENDED };

class TaskManager {
public:
	TaskManager();
	~TaskManager();
	void postTask(Task *task);
	void execute();
	void pause();
	void resume();
	void finish();
	float getProgress() const;
	TaskEventsBroadcaster *getTaskEventsBroadcaster();
	TasksExecutionState getExecutionState() const;
	unsigned getTaskCount() const;

private:
	TasksExecutionState state;
	boost::asio::io_service service;
	boost::thread_group threadpool;
	boost::asio::io_service::work work;
	unsigned taskCount;
	TaskEventsBroadcaster stats;
};
