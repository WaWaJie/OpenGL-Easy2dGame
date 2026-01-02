#ifndef _TIMER_H_
#define _TIMER_H_

#include<functional>

class Timer
{
public:
	Timer() = default;
	~Timer() = default;

public:
	void set_wait_time(double wait_time)
	{
		this->wait_time = wait_time;
	}

	void set_one_shot(bool flag)
	{
		one_shot = flag;
	}

	void pause()
	{
		paused = true;
	}

	void resume()
	{
		paused = false;
	}

	void restart()
	{
		pass_time = 0;
		shotted = false;
	}

	void set_on_timeout(std::function<void()>on_timeout)
	{
		this->on_timeout = on_timeout;
	}

	void on_update(double delta)
	{
		if (paused)return;

		pass_time += delta;
		if (pass_time >= wait_time)
		{
			shotted = true;
			bool can_shot = (shotted && one_shot) || !one_shot;
			if (can_shot && on_timeout)
				on_timeout();

			pass_time -= wait_time;
		}
	}

private:
	double wait_time = 0;
	double pass_time = 0;
	bool one_shot = false;
	bool shotted = false;
	bool paused = false;
	std::function<void()>on_timeout;
};

#endif // !_TIMER_H_
