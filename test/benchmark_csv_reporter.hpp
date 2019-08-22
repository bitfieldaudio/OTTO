#pragma once

//#include "testing.t.hpp"

namespace Catch {

  struct BenchmarkCSVReporter : StreamingReporterBase<BenchmarkCSVReporter> {
    BenchmarkCSVReporter(ReporterConfig const& _config) : StreamingReporterBase(_config) {
      stream << "Name, Iterations, Mean (ns), StdDev (ns)\n";
    }

    static std::string getDescription()
    {
      return "Reports only benchmarks to a benchmarks.csv file";
    }

    void assertionStarting(AssertionInfo const&) override {}
    bool assertionEnded(AssertionStats const&) override
    {
      return true;
    }

    void benchmarkPreparing(std::string const& str) override
    {
      //stream << "Preparing " << str;
    }
    void benchmarkStarting(BenchmarkInfo const& info) override
    {
      //stream << "Starting " << info.name;
    }
    void benchmarkEnded(BenchmarkStats<> const& stats) override
    {
      stream << fmt::format("\"{}\", {}, {}, {}\n", stats.info.name, stats.info.iterations, stats.mean.point.count(), stats.standardDeviation.point.count());
    }
    void benchmarkFailed(std::string const& str) override
    {
      //stream << "Failed " << str;
    }
  };

  CATCH_REGISTER_REPORTER("benchmarks.csv", BenchmarkCSVReporter);

} // namespace Catch
