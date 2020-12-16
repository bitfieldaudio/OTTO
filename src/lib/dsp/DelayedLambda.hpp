#include <functional>

#include <Gamma/Domain.h>

template<class Td = gam::DomainObserver>
class DelayedLambda : public Td {
public:
  DelayedLambda(float delay_in_s, std::function<void()> fct) : fct_(fct)
  {
    delay_in_samples = delay_in_s * Td::spu();
  };

  void operator()();
  void reset();
  void finish();

private:
  int delay_in_samples = 0;
  int mDel = 0;
  bool running = false;
  std::function<void()> fct_;
};

template<class Td>
void DelayedLambda<Td>::operator()()
{
  if (mDel == delay_in_samples) {
    fct_();
    mDel++;
    running = false;
  }
  if (running) mDel++;
}

template<class Td>
void DelayedLambda<Td>::reset()
{
  mDel = 0;
  running = true;
}

template<class Td>
void DelayedLambda<Td>::finish()
{
  mDel = delay_in_samples + 1;
  running = false;
}