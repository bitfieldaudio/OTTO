#include "testing.t.hpp"

#include <thread>

#include "util/crtp.hpp"
#include "util/flat_map.hpp"
#include "util/ptr_vec.hpp"
#include "util/string_ref.hpp"
#include "util/thread.hpp"

#define DBUS_HAS_RECURSIVE_MUTEX 1
#include <dbus-c++/dbus.h>

#include "boards/rpi/connman_agent_adaptor.hpp"
#include "boards/rpi/connman_dbus_proxy.hpp"

namespace otto::board::wifi {

  struct IProperty {
    virtual ~IProperty() = default;
    virtual const std::string& name() const = 0;

  protected:
    friend struct HasProperties;
    virtual void set_raw(const DBus::Variant& value) = 0;
  };

  struct HasProperties {
    HasProperties() = default;
    HasProperties(const HasProperties&) = delete;
    HasProperties& operator=(const HasProperties&) = delete;
    HasProperties& operator=(HasProperties&&) = delete;

    virtual ~HasProperties() = default;

    virtual void SetProperty(const std::string& name, const ::DBus::Variant& value) = 0;
    virtual std::map<std::string, ::DBus::Variant> GetProperties() = 0;

    void PropertyChanged(const std::string& name, const ::DBus::Variant& value)
    {
      auto found = nano::find(properties_, name, &IProperty::name);
      if (found != properties_.end()) {
        (*found)->set_raw(value);
      }
    }

    void UpdateProperties()
    {
      set_properties_raw(GetProperties());
    }

    void set_properties_raw(const std::map<std::string, ::DBus::Variant>& props)
    {
      for (auto&& [name, val] : props) {
        PropertyChanged(name, val);
      }
    }

  protected:
    template<typename T, bool Writable>
    friend struct Property;

    std::vector<IProperty*> properties_;
  };

  template<typename T, bool Writable>
  struct Property : IProperty {
    Property(util::string_ref name, HasProperties* owner) : owner(*owner), name_(name)
    {
      owner->properties_.push_back(this);
    }

    const std::string& name() const override
    {
      return name_;
    }

    void set_raw(const DBus::Variant& value) override
    {
      auto iter = value.reader();
      iter >> value_;
      on_change.emit(value_);
    }

    const T& get() const noexcept
    {
      return value_;
    }

    operator const T&() const noexcept
    {
      return get();
    }

    util::Signal<T> on_change;

  protected:
    HasProperties& owner;
    std::string name_;
    T value_{};
  };

  template<typename T>
  struct Property<T, true> : Property<T, false> {
    Property(util::string_ref name, HasProperties* owner) : Property<T, false>(name, owner) {}

    void set(const T& value)
    {
      DBus::Variant val;
      auto i = val.writer();
      i << value;
      this->owner.SetProperty(this->name(), val);
    }

    Property& operator=(const T& val)
    {
      set(val);
      return *this;
    }
  };

  template<typename T, bool W, typename O>
  bool operator==(O&& value, const Property<T, W>& prop)
  {
    return value == prop.get();
  }

  template<typename T, bool W, typename O>
  bool operator==(const Property<T, W>& prop, O&& value)
  {
    return prop.get() == value;
  }

  template<typename Derived, typename Interface>
  struct ProxyBase : util::crtp<Derived, ProxyBase<Derived, Interface>>, HasProperties, Interface, DBus::ObjectProxy {
    ProxyBase(DBus::Connection& connection, util::string_ref path, util::string_ref service)
      : DBus::ObjectProxy(connection, path.c_str(), service.c_str())
    {}

    void SetProperty(const std::string& name, const ::DBus::Variant& value) override
    {
      dynamic_cast<Interface&>(*this).SetProperty(name, value);
    }

    std::map<std::string, DBus::Variant> GetProperties() override
    {
      return dynamic_cast<Interface&>(*this).GetProperties();
    }

    void PropertyChanged(const std::string& name, const ::DBus::Variant& value) override
    {
      this->HasProperties::PropertyChanged(name, value);
    }
  };

  struct TechnologyProxy : ProxyBase<TechnologyProxy, net::connman::Technology_proxy> {
    TechnologyProxy(DBus::Connection& connection, util::string_ref path)
      : ProxyBase(connection, path.c_str(), "net.connman")
    {}

    Property<bool, true> Powered = {"Powered", this};
    Property<bool, false> Connected = {"Connected", this};
    Property<std::string, false> Name = {"Name", this};
    Property<std::string, false> Type = {"Type", this};
    Property<bool, true> Tethering = {"Tethering", this};
    Property<std::string, true> TetheringIdentifier = {"TetheringIdentifier", this};
    Property<std::string, true> TetheringPassphrase = {"TetheringPassphrase", this};
  };

  struct ServiceProxy : ProxyBase<ServiceProxy, net::connman::Service_proxy> {
    ServiceProxy(DBus::Connection& connection, util::string_ref path)
      : ProxyBase(connection, path.c_str(), "net.connman")
    {}

    bool connected()
    {
      return State == "ready" || State == "online";
    }

    ///
    /// The service state information.
    ///
    /// Valid states are "idle", "failure", "association",
    /// "configuration", "ready", "disconnect" and "online".
    ///
    /// The "ready" state signals a successfully
    /// connected device. "online" signals that an
    /// Internet connection is available and has been
    /// verified.
    ///
    /// See doc/overview-api.txt for more information about
    /// state transitions.
    ///
    Property<std::string, false> State = {"State", this};
    ///
    /// The service error status details.
    ///
    /// When error occur during connection or disconnection
    /// the detailed information is represented in this
    /// property to help the user interface to present the
    /// user with alternate options.
    ///
    /// This property is only valid when the service is in
    /// the "failure" state. Otherwise it might be empty or
    /// not present at all.
    ///
    /// Current defined error code is "dhcp-failed".
    ///
    Property<std::string, false> Error = {"Error", this};
    ///
    /// The service name (for example "Wireless" etc.)
    ///
    /// This name can be used for directly displaying it in
    /// the application. It has pure informational purpose
    /// and no attempt should be made to translate it.
    ///
    /// For Ethernet devices and hidden WiFi networks this
    /// property is not present.
    ///
    Property<std::string, false> Name = {"Name", this};
    ///
    /// The service type (for example "ethernet", "wifi" etc.)
    ///
    /// This information should only be used to determine
    /// advanced properties or showing the correct icon
    /// to the user.
    ///
    /// Together with a missing Name property, this can
    /// be used to identify hidden WiFi networks.
    ///
    Property<std::string, false> Type = {"Type", this};
    ///
    /// If the service type is WiFi, then this property is
    /// present and contains the list of security methods
    /// or key management settings.
    ///
    /// Possible values are "none", "wep", "psk", "ieee8021x"
    /// and also "wps".
    ///
    /// This property might be only present for WiFi
    /// services.
    ///
    Property<std::vector<std::string>, false> Security = {"Security", this};
    ///
    /// Indicates the signal strength of the service. This
    /// is a normalized value between 0 and 100.
    ///
    /// This property will not be present for Ethernet
    /// devices.
    ///
    Property<std::uint8_t, false> Strength = {"Strength", this};
    ///
    /// Will be true if a cable is plugged in or the user
    /// selected and successfully connected to this service.
    ///
    /// This value is automatically changed and to revert
    /// it back to false the Remove() method needs to be
    /// used.
    ///
    Property<bool, false> Favorite = {"Favorite", this};
    ///
    /// This value will be set to true if the service is
    /// configured externally via a configuration file.
    ///
    /// The only valid operation are Connect() and of
    /// course Disconnect(). The Remove() method will
    /// result in an error.
    ///
    Property<bool, false> Immutable = {"Immutable", this};
    ///
    /// If set to true, this service will auto-connect
    /// when no other connection is available.
    ///
    /// The service won't auto-connect while roaming.
    ///
    /// For favorite services it is possible to change
    /// this value to prevent or permit automatic
    /// connection attempts.
    ///
    Property<bool, true> AutoConnect = {"AutoConnect", this};
    ///
    /// This property indicates if this service is roaming.
    ///
    /// In the case of Cellular services this normally
    /// indicates connections to a foreign provider when
    /// traveling abroad.
    ///
    Property<bool, false> Roaming = {"Roaming", this};
    ///
    /// The list of currently active nameservers for this
    /// service. If the server is not in READY or ONLINE
    /// state than this list will be empty.
    ///
    /// Global nameservers are automatically added to this
    /// list. The array represents a sorted list of the
    /// current nameservers. The first one has the highest
    /// priority and is used by default.
    ///
    /// When using DHCP this array represents the nameservers
    /// provided by the network. In case of manual settings,
    /// the ones from Nameservers.Configuration are used.
    ///
    Property<std::vector<std::string>, false> Nameservers = {"Nameservers", this};
    ///
    /// The list of manually configured domain name
    /// servers. Some cellular networks don't provide
    /// correct name servers and this allows for an
    /// override.
    ///
    /// This array is sorted by priority and the first
    /// entry in the list represents the nameserver with
    /// the highest priority.
    ///
    /// When using manual configuration and no global
    /// nameservers are configured, then it is useful
    /// to configure this setting.
    ///
    /// Changes to the domain name servers can be done
    /// at any time. It will not cause a disconnect of
    /// the service. However there might be small window
    /// where name resolution might fail.
    ///
    Property<std::vector<std::string>, true> Nameservers_Configuration = {"Nameservers.Configuration", this};
    ///
    /// The list of currently active timeservers for this
    /// service. If the server is not in READY or ONLINE
    /// state than this list will be empty.
    ///
    Property<std::vector<std::string>, false> Timeservers = {"Timeservers", this};
    ///
    /// The list of manually configured time servers.
    ///
    /// The first entry in the list represents the
    /// timeserver with the highest priority.
    ///
    /// When using manual configuration this setting
    /// is useful to override all the other timeserver
    /// settings. This is service specific, hence only
    /// the values for the default service are used.
    ///
    /// Changes to this property will result in restart
    /// of NTP query.
    ///
    Property<std::vector<std::string>, true> Timeservers_Configuration = {"Timerservers.Configuration", this};
    ///
    /// The list of currently used search domains taken
    /// from Domains.Configurations if set, otherwise a
    /// domain name if provided by DHCP or VPNs.
    ///
    Property<std::vector<std::string>, false> Domains = {"Domains", this};
    ///
    /// The list of manually configured search domains.
    ///
    Property<std::vector<std::string>, true> Domains_Configuration = {"Domains.Configuration", this};
  };

  struct ManagerProxy : ProxyBase<ManagerProxy, net::connman::Manager_proxy> {
    ManagerProxy(DBus::Connection& connection) : ProxyBase(connection, "/", "net.connman")
    {
      UpdateProperties();
    }

    util::unique_ptr_vec<TechnologyProxy> GetTechnologies()
    {
      auto all = this->ProxyBase::GetTechnologies();
      util::unique_ptr_vec<TechnologyProxy> res;
      res.reserve(all.size());
      for (auto&& pair : all) {
        auto& tech = res.emplace_back(this->conn(), pair._1.c_str());
        tech.set_properties_raw(pair._2);
      }
      return res;
    }

    util::unique_ptr_vec<ServiceProxy> GetServices()
    {
      auto all = this->ProxyBase::GetServices();
      util::unique_ptr_vec<ServiceProxy> res;
      res.reserve(all.size());
      for (auto&& pair : all) {
        auto& service = res.emplace_back(this->conn(), pair._1.c_str());
        service.set_properties_raw(pair._2);
      }
      return res;
    }

    Property<std::string, false> State = {"State", this};
    Property<bool, true> OfflineMode = {"OfflineMode", this};
  };

  struct AgentField {
    static tl::optional<AgentField> from_fields(std::string name, const DBus::Variant& fields_var)
    {
      bool informational = false;
      std::string value;

      std::map<std::string, ::DBus::Variant> fields;
      auto var_reader = fields_var.reader();
      var_reader >> fields;
      for (auto&& [key, val] : fields) {
        auto reader = val.reader();
        if (key == "Requirement") {
          std::string req;
          reader >> req;
          if (req == "optional" || req == "alternate") return tl::nullopt;
          informational = req == "Informational";
        } else if (key == "Value") {
          reader >> value;
        }
      }

      return AgentField{.name = name, .informational = informational, .value = value};
    }

    std::string name;
    bool informational = false;
    std::string value;
  };

  struct AgentAdaptor : net::connman::Agent_adaptor, DBus::ObjectAdaptor {
    AgentAdaptor(DBus::Connection& conn) : DBus::ObjectAdaptor(conn, "/otto/connman/agent") {}

    void Release(::DBus::Error& error) override
    {
      LOGI("Releasing agent");
    }
    void ReportError(const ::DBus::Path& service, const std::string& error_str, ::DBus::Error& error) override
    {
      LOGI("Agent::ReportError: {}", error_str);
    }
    void RequestBrowser(const ::DBus::Path& service, const std::string& url, ::DBus::Error& error) override
    {
      LOGI("Agent::RequestBrowser: url: {}", url);
    }
    std::map<std::string, ::DBus::Variant> RequestInput(const ::DBus::Path& service,
                                                        const std::map<std::string, ::DBus::Variant>& fields,
                                                        ::DBus::Error& error) override
    {
      LOGI("Request Input: ");
      auto field_objs = util::view::to_vec(
        nano::views::transform(fields, [](auto&& pair) { return std::apply(AgentField::from_fields, pair); }) |
        nano::views::filter(MEMBER_CALLER(has_value)) | nano::views::transform(MEMBER_CALLER(value)));
      std::map<std::string, DBus::Variant> res;
      for (auto&& field : field_objs) {
        LOGI("Field: {}, informational: {}, value: '{}'", field.name, field.informational, field.value);
        if (!field.informational) {
          DBus::Variant var;
          auto iter = var.writer();
          std::string value;
          std::cout << field.name << "?: ";
          std::cin >> value;
          iter << value;
          res[field.name] = var;
        }
      }
      return res;
    }
  };

  void main()
  {
    DBus::BusDispatcher dispatcher;
    DBus::default_dispatcher = &dispatcher;

    DBus::Connection client_conn = DBus::Connection::SystemBus();

    util::thread dbus_thread = util::thread([](auto&& should_run) {
      LOGI("Entering dbus main loop");
      DBus::default_dispatcher->enter();
      LOGI("Exiting dbus main loop");
    });
    client_conn.set_timeout(30 * 1000);
    ManagerProxy manager = {client_conn};
    LOGI("connman state: {}", manager.State.get());

    // manager.OfflineMode = true;
    // LOGI("Offline mode set to {}", manager.OfflineMode.get());

    auto technologies = manager.GetTechnologies();

    for (auto& t : technologies) {
      LOGI("Technology: Name: {}, Powered: {}, Connected: {}, Type: {}", t.Name.get(), t.Powered.get(),
           t.Connected.get(), t.Type.get());
    }

    auto wifi = nano::find_if(technologies, [](auto&& t) { return t.Type == "wifi"; });

    if (wifi == technologies.end()) {
      LOGW("No wifi technology found");
      return;
    }
    if (!wifi->Powered) wifi->Powered = true;
    LOGI("Scanning");
    wifi->Scan();
    LOGI("scan done");

    auto services = manager.GetServices();
    LOGI("Services:");
    for (auto&& [i, s] : util::view::indexed(services)) {
      LOGI(" {} - Name: {}, State: {}, Type: {}, Security: [{}]", i, s.Name.get(), s.State.get(), s.Type.get(),
           util::join_strings(s.Security.get()));
    }
    int i = 0;
    LOGI("Select one [0]:");
    std::cin >> i;

    auto& service = services.at(i);


    AgentAdaptor agent = {client_conn};

    manager.RegisterAgent(agent.path());
    LOGI("Connecting to {}", service.Name.get());
    if (!service.connected()) service.Connect();
    LOGI("State: {}", service.State.get());
    manager.UnregisterAgent(agent.path());

    dispatcher.leave();
  }
} // namespace otto::board::wifi
