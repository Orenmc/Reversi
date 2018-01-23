/*
 * Task.h
 *
 *  Created on: Jan 23, 2018
 *      Author: oren
 */

#ifndef TASK_H_
#define TASK_H_

class Task {
public:
	Task(void * (*func)(void *arg), void* arg) :
		func(func), arg(arg) {}
	void execute() {
		func(arg);
	}
	virtual ~Task() {}
private:
	void * (*func)(void *arg);
	void *arg;
};

#endif /* TASK_H_ */
