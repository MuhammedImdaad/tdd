#include <ThreadPool.h>

void ThreadPool::job()
{
    while (true)
    {
        std::unique_lock<std::mutex> lock(m);
        workAdded.wait(lock, [this]()
                       {
                        //    std::cout << std::this_thread::get_id() << " Thread waiting..." << q.size() << "\n";
                           return done || !q.empty(); // task ahead
                       });

        if (workComplete()) // task is complete
        {
            // std::cout << std::this_thread::get_id() << " Thread exiting...\n";
            return;
        }

        Work work = pullWork();
        lock.unlock();
        // std::cout << std::this_thread::get_id() << " Executing work...\n";
        work.execute();
    }
}

void ThreadPool::stop()
{
    done = true;
    workAdded.notify_all();
    // std::cout << std::this_thread::get_id() << " Notified worker threads to stop\n";
    for (auto &workerThread : workerThreads)
        if (workerThread.joinable())
            workerThread.join();
}

bool ThreadPool::hasWork()
{
    std::lock_guard<std::mutex> lock(m);
    return !done && !q.empty();
}

bool ThreadPool::workComplete() const
{
    return done && q.empty();
}
void ThreadPool::add(Work w)
{
    {
        std::lock_guard<std::mutex> lock(m);
        q.push(w);
        // std::cout << std::this_thread::get_id() << " Work added to queue\n";
    }
    workAdded.notify_one();
    // std::cout << std::this_thread::get_id() << " Notified worker threads\n";
}

Work ThreadPool::pullWork()
{
    // std::cout << std::this_thread::get_id() << " pulling out " << q.size() << "\n";
    Work out;
    if (q.empty())
        return out;

    out = q.front();
    q.pop();
    // std::cout << std::this_thread::get_id() << " pulled out\n";
    return out;
}

void ThreadPool::start(int numberOfThreads)
{
    for (unsigned int i{0}; i < numberOfThreads; i++)
    {
        workerThreads.push_back(std::thread(&ThreadPool::job, this));
        // std::cout << "Thread " << workerThreads[i].get_id() << " started\n";
    }
}

ThreadPool::~ThreadPool()
{
    stop();
    // std::cout << std::this_thread::get_id() << " going off\n";
}