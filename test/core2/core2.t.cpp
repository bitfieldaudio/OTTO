#include "testing.t.hpp"

#include "core2/core2.hpp"

namespace otto::core2 {

  TEST_CASE ("ActionReciever") {
    using void_action = Action<struct void_action_tag>;
    using int_action = Action<struct int_action_tag, int>;

    struct VoidAR {
      void action(void_action)
      {
        has_run = true;
      }
      bool has_run = false;
    };

    struct IntAR {
      void action(int_action, int val)
      {
        value += val;
      }
      int value = 0;
    };

    SECTION ("The ActionReciever concept") {
      struct EmptyStruct {};

      static_assert(ActionReciever::is<VoidAR, void_action>);
      static_assert(!ActionReciever::is<EmptyStruct, void_action>);
    }

    SECTION ("ActionData can be created using Action::data") {
      auto ad = int_action::data(10);
      static_assert(std::is_same_v<decltype(ad), ActionData<int_action>>);
      REQUIRE(std::get<0>(ad.args) == 10);
    }

    SECTION ("Action with no data can be recieved using call_reciever") {
      VoidAR void_ar;

      REQUIRE(void_ar.has_run == false);
      call_reciever(void_ar, void_action::data());
      REQUIRE(void_ar.has_run == true);
    }

    SECTION ("Action with an int argument can be recieved using call_reciever") {
      IntAR int_ar;

      call_reciever(int_ar, int_action::data(10));
      REQUIRE(int_ar.value == 10);
    }

    SECTION ("try_call_reciever calls action reciever and returns true") {
      IntAR int_ar;

      REQUIRE(try_call_reciever(int_ar, int_action::data(10)));
      REQUIRE(int_ar.value == 10);
    }

    SECTION ("try_call_reciever returns false when no reciever avaliable") {
      IntAR int_ar;
      REQUIRE(!try_call_reciever(int_ar, void_action::data()));
      REQUIRE(int_ar.value == 0);
    }

    SECTION ("ActionQueue") {
      ActionQueue aq;
      SECTION ("ActionQueue is initially empty") {
        REQUIRE(aq.size() == 0);
      }

      SECTION ("ActionQueue.push(function)") {
        bool has_run = false;
        aq.push([&] { has_run = true; });
        REQUIRE(aq.size() == 1);
        aq.pop()();
        REQUIRE(has_run);
      }

      SECTION ("ActionQueue.pop_call_all()") {
        IntAR iar;
        VoidAR var;
        aq.push(var, void_action::data());
        aq.push(iar, int_action::data(10));
        REQUIRE(aq.size() == 2);
        aq.pop_call_all();
        REQUIRE(var.has_run);
        REQUIRE(iar.value == 10);
      }

      SECTION ("ActionQueue.push(function) is FIFO ordered") {
        bool has_run = false;
        aq.push([&] { has_run = true; });
        aq.push([&] { REQUIRE(has_run); });
        REQUIRE(aq.size() == 2);
        aq.pop_call_all();
        REQUIRE(has_run);
      }

      SECTION ("ActionQueue.push(ActionReciever, ActionData) works") {
        VoidAR ar;
        aq.push(ar, void_action::data());
        aq.pop_call();
        REQUIRE(ar.has_run);
      }


      SECTION ("ActionQueue.try_push(ActionReciever, ActionData) works") {
        IntAR ar;
        aq.try_push(ar, int_action::data(10));
        aq.pop_call();
        REQUIRE(ar.value == 10);
      }

      SECTION ("ActionQueue.try_push(ActionReciever, ActionData) does not enqueue an action if the reciever cannot "
               "recieve it") {
        IntAR ar;
        REQUIRE(aq.try_push(ar, void_action::data()) == false);
        REQUIRE(aq.size() == 0);
      }
    }

    SECTION ("ActionQueueHelper") {
      struct OtherIntAR {
        void action(int_action, int val)
        {
          value += val;
        }
        int value = 0;
      } oiar;
      ActionQueue queue;
      VoidAR var;
      IntAR iar;
      ActionQueueHelper aqh = {queue, var, iar, oiar};

      SECTION ("ActionQueueHelper holds references to recievers") {
        REQUIRE(&aqh.reciever<VoidAR>() == &var);
        REQUIRE(&aqh.reciever<IntAR>() == &iar);
        REQUIRE(&aqh.reciever<OtherIntAR>() == &oiar);
      }

      SECTION ("ActionQueueHelper queues actions to all recievers") {
        aqh.push(int_action::data(10));
        REQUIRE(queue.size() == 2);
        queue.pop_call_all();
        REQUIRE(iar.value == 10);
        REQUIRE(oiar.value == 10);
      }

      SECTION ("ActionQueueHelper is copy constructible") {
        auto aqh2 = aqh;
        REQUIRE(&aqh.reciever<VoidAR>() == &var);
        REQUIRE(&aqh2.reciever<VoidAR>() == &var);
      }
    }

    SECTION ("Action with reference parameter") {
      using ref_act = Action<struct ref_act_tag, int&>;
      struct RefAR {
        void action(ref_act, int& ref) {
          addr = &ref;
        };
        int* addr = nullptr;
      };
      int an_int = 0;
      RefAR rar;
      call_reciever(rar, ref_act::data(an_int));
      REQUIRE(rar.addr == &an_int);
    }
  }

} // namespace otto::core2
