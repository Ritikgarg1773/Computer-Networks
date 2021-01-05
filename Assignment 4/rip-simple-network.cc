 #include <fstream>
 #include "ns3/core-module.h"
 #include "ns3/internet-module.h"
 #include "ns3/csma-module.h"
 #include "ns3/internet-apps-module.h"
 #include "ns3/ipv4-static-routing-helper.h"
 #include "ns3/ipv4-routing-table-entry.h"
 
 using namespace ns3;
 
 NS_LOG_COMPONENT_DEFINE ("RipSimpleRouting");
 
 void TearDownLink (Ptr<Node> nodeA, Ptr<Node> nodeB, uint32_t interfaceA, uint32_t interfaceB)
 {
   nodeA->GetObject<Ipv4> ()->SetDown (interfaceA);
   nodeB->GetObject<Ipv4> ()->SetDown (interfaceB);
 }
 
 int main (int argc, char **argv)
 {
   bool verbose = false;
   bool printRoutingTables = false;
   bool showPings = false;
   std::string SplitHorizon ("PoisonReverse");
 
   CommandLine cmd;
   cmd.AddValue ("verbose", "turn on log components", verbose);
   cmd.AddValue ("printRoutingTables", "Print routing tables at 30, 60 and 90 seconds", printRoutingTables);
   cmd.AddValue ("showPings", "Show Ping6 reception", showPings);
   cmd.AddValue ("splitHorizonStrategy", "Split Horizon strategy to use (NoSplitHorizon, SplitHorizon, PoisonReverse)", SplitHorizon);
   cmd.Parse (argc, argv);
 
   if (verbose)
     {
       LogComponentEnableAll (LogLevel (LOG_PREFIX_TIME | LOG_PREFIX_NODE));
       LogComponentEnable ("RipSimpleRouting", LOG_LEVEL_INFO);
       LogComponentEnable ("Rip", LOG_LEVEL_ALL);
       LogComponentEnable ("Ipv4Interface", LOG_LEVEL_ALL);
       LogComponentEnable ("Icmpv4L4Protocol", LOG_LEVEL_ALL);
       LogComponentEnable ("Ipv4L3Protocol", LOG_LEVEL_ALL);
       LogComponentEnable ("ArpCache", LOG_LEVEL_ALL);
       LogComponentEnable ("V4Ping", LOG_LEVEL_ALL);
     }
 
   if (SplitHorizon == "NoSplitHorizon")
     {
       Config::SetDefault ("ns3::Rip::SplitHorizon", EnumValue (RipNg::NO_SPLIT_HORIZON));
     }
   else if (SplitHorizon == "SplitHorizon")
     {
       Config::SetDefault ("ns3::Rip::SplitHorizon", EnumValue (RipNg::SPLIT_HORIZON));
     }
   else
     {
       Config::SetDefault ("ns3::Rip::SplitHorizon", EnumValue (RipNg::POISON_REVERSE));
     }
 
   NS_LOG_INFO ("Create nodes."); //add the message
  //set1
   Ptr<Node> a = CreateObject<Node> ();
   Names::Add ("A", a);
   Ptr<Node> b = CreateObject<Node> ();
   Names::Add ("B", b);
   Ptr<Node> c = CreateObject<Node> ();
   Names::Add ("C", c);
   Ptr<Node> r1 = CreateObject<Node> ();
   Names::Add ("R1", r1);
  //set2
   Ptr<Node> d = CreateObject<Node> ();
   Names::Add ("D", d);
   Ptr<Node> e = CreateObject<Node> ();
   Names::Add ("E", e);
   Ptr<Node> f = CreateObject<Node> ();
   Names::Add ("F", f);
   Ptr<Node> g = CreateObject<Node> ();
   Names::Add ("G", g);
   Ptr<Node> r2 = CreateObject<Node> ();
   Names::Add ("R2", r2);
  // two more routers
   Ptr<Node> r3 = CreateObject<Node> ();
   Names::Add ("R3", r3);
   Ptr<Node> r4 = CreateObject<Node> ();
   Names::Add ("R4",r4);
  //set3
   Ptr<Node> h = CreateObject<Node> ();
   Names::Add ("H", h);
   Ptr<Node> i = CreateObject<Node> ();
   Names::Add ("I", i);
   Ptr<Node>  r5 = CreateObject<Node> ();
   Names::Add ("R5", r5);
  //set 6
   Ptr<Node> j = CreateObject<Node> ();
   Names::Add ("J", j);
   Ptr<Node> k = CreateObject<Node> ();
   Names::Add ("K", k);
   Ptr<Node> r6 = CreateObject<Node> ();
   Names::Add ("R6", r6);
  
   //connecting
   NodeContainer net1 (a, r1);   //r1->1
   NodeContainer net2 (b, r1);   // r1-> 2
   NodeContainer net3 (c, r1);   //r1 : 3
   NodeContainer net4 (r1, r3);  // r1 : 4, r3: 1
   NodeContainer net5 (d, r2);   // r2 : 1
   NodeContainer net6 (e, r2);   // r2: 2
   NodeContainer net7 (f, r2);   // r2 :3
   NodeContainer net8 (g, r2);   // r2: 4
   NodeContainer net9 (r4, r2);  // r2: 5, r4: 1
   NodeContainer net10 (r3, r4);  //r3: 2, r4: 2
   NodeContainer net11 (h, r5);   // r5:1
   NodeContainer net12 (i, r5);   // r5: 2
   NodeContainer net13 (r5, r3);  // r5: 3, r3: 3
   NodeContainer net14 (r4, r5);  // r5:4, r4: 3
   NodeContainer net15 (j, r6);   // r6: 1
   NodeContainer net16 (k, r6);  // r6:2
   NodeContainer net17 (r6, r4);  // r6:3, r4 : 4
   NodeContainer routers (r1, r2, r3, r4, r5);
   routers.Add(r6);
   NodeContainer nodes (a,b,c,d,e);
   nodes.Add(f);
   nodes.Add(g);
   nodes.Add(h);
   nodes.Add(i);
   nodes.Add(j);
   nodes.Add(k);
 
 
   NS_LOG_INFO ("Create channels.");
   CsmaHelper csma;
   csma.SetChannelAttribute ("DataRate", DataRateValue (5000000));
   csma.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (2)));
   NetDeviceContainer ndc1 = csma.Install (net1);
   NetDeviceContainer ndc2 = csma.Install (net2);
   NetDeviceContainer ndc3 = csma.Install (net3);
   NetDeviceContainer ndc4 = csma.Install (net4);
   NetDeviceContainer ndc5 = csma.Install (net5);
   NetDeviceContainer ndc6 = csma.Install (net6);
   NetDeviceContainer ndc7 = csma.Install (net7);
   NetDeviceContainer ndc8 = csma.Install (net8);
   NetDeviceContainer ndc9 = csma.Install (net9);
   NetDeviceContainer ndc10 = csma.Install (net10);
   NetDeviceContainer ndc11 = csma.Install (net11);
   NetDeviceContainer ndc12 = csma.Install (net12);
   NetDeviceContainer ndc13 = csma.Install (net13);
   NetDeviceContainer ndc14 = csma.Install (net14);
   NetDeviceContainer ndc15 = csma.Install (net15);
   NetDeviceContainer ndc16 = csma.Install (net16);
   NetDeviceContainer ndc17 = csma.Install (net17);
 
   NS_LOG_INFO ("Create IPv4 and routing");
   RipHelper ripRouting;
 
   // Rule of thumb:
   // Interfaces are added sequentially, starting from 0
   // However, interface 0 is always the loopback...
   ripRouting.ExcludeInterface (r1, 1);
   ripRouting.ExcludeInterface (r1, 2);
   ripRouting.ExcludeInterface (r1, 3);
   ripRouting.ExcludeInterface (r2, 1);
   ripRouting.ExcludeInterface (r2, 2);
   ripRouting.ExcludeInterface (r2, 3);
   ripRouting.ExcludeInterface (r2, 4);
   ripRouting.ExcludeInterface (r5, 1);
   ripRouting.ExcludeInterface (r5, 2);
   ripRouting.ExcludeInterface (r6, 1);
   ripRouting.ExcludeInterface (r6, 2);
 
   ripRouting.SetInterfaceMetric (r5, 4, 5);
   ripRouting.SetInterfaceMetric (r4, 3, 5);
 
   Ipv4ListRoutingHelper listRH;
   listRH.Add (ripRouting, 0);
 //  Ipv4StaticRoutingHelper staticRh;
 //  listRH.Add (staticRh, 5);
 
   InternetStackHelper internet;
   internet.SetIpv6StackInstall (false);
   internet.SetRoutingHelper (listRH);
   internet.Install (routers);
 
   InternetStackHelper internetNodes;
   internetNodes.SetIpv6StackInstall (false);
   internetNodes.Install (nodes);
 
   // Assign addresses.
   // The source and destination networks have global addresses
   // The "core" network just needs link-local addresses for routing.
   // We assign global addresses to the routers as well to receive
   // ICMPv6 errors.
   NS_LOG_INFO ("Assign IPv4 Addresses.");
   Ipv4AddressHelper ipv4;
 
   ipv4.SetBase (Ipv4Address ("10.0.0.0"), Ipv4Mask ("255.255.255.0"));
   Ipv4InterfaceContainer iic1 = ipv4.Assign (ndc1);
 
   ipv4.SetBase (Ipv4Address ("10.0.1.0"), Ipv4Mask ("255.255.255.0"));
   Ipv4InterfaceContainer iic2 = ipv4.Assign (ndc2);
 
   ipv4.SetBase (Ipv4Address ("10.0.2.0"), Ipv4Mask ("255.255.255.0"));
   Ipv4InterfaceContainer iic3 = ipv4.Assign (ndc3);
 
   ipv4.SetBase (Ipv4Address ("10.0.3.0"), Ipv4Mask ("255.255.255.0"));
   Ipv4InterfaceContainer iic4 = ipv4.Assign (ndc4);
 
   ipv4.SetBase (Ipv4Address ("10.0.4.0"), Ipv4Mask ("255.255.255.0"));
   Ipv4InterfaceContainer iic5 = ipv4.Assign (ndc5);
 
   ipv4.SetBase (Ipv4Address ("10.0.5.0"), Ipv4Mask ("255.255.255.0"));
   Ipv4InterfaceContainer iic6 = ipv4.Assign (ndc6);
 
   ipv4.SetBase (Ipv4Address ("10.0.6.0"), Ipv4Mask ("255.255.255.0"));
   Ipv4InterfaceContainer iic7 = ipv4.Assign (ndc7);
 
   ipv4.SetBase (Ipv4Address ("10.0.7.0"), Ipv4Mask ("255.255.255.0"));
   Ipv4InterfaceContainer iic8 = ipv4.Assign (ndc8);

   ipv4.SetBase (Ipv4Address ("10.0.8.0"), Ipv4Mask ("255.255.255.0"));
   Ipv4InterfaceContainer iic9 = ipv4.Assign (ndc9);

   ipv4.SetBase (Ipv4Address ("10.0.9.0"), Ipv4Mask ("255.255.255.0"));
   Ipv4InterfaceContainer iic10 = ipv4.Assign (ndc10);

   ipv4.SetBase (Ipv4Address ("10.0.10.0"), Ipv4Mask ("255.255.255.0"));
   Ipv4InterfaceContainer iic11 = ipv4.Assign (ndc11);

   ipv4.SetBase (Ipv4Address ("10.0.11.0"), Ipv4Mask ("255.255.255.0"));
   Ipv4InterfaceContainer iic12 = ipv4.Assign (ndc12);

   ipv4.SetBase (Ipv4Address ("10.0.12.0"), Ipv4Mask ("255.255.255.0"));
   Ipv4InterfaceContainer iic13 = ipv4.Assign (ndc13);

   ipv4.SetBase (Ipv4Address ("10.0.13.0"), Ipv4Mask ("255.255.255.0"));
   Ipv4InterfaceContainer iic14 = ipv4.Assign (ndc14);

   ipv4.SetBase (Ipv4Address ("10.0.14.0"), Ipv4Mask ("255.255.255.0"));
   Ipv4InterfaceContainer iic15 = ipv4.Assign (ndc15);
 
   ipv4.SetBase (Ipv4Address ("10.0.15.0"), Ipv4Mask ("255.255.255.0"));
   Ipv4InterfaceContainer iic16 = ipv4.Assign (ndc16);

   ipv4.SetBase (Ipv4Address ("10.0.16.0"), Ipv4Mask ("255.255.255.0"));
   Ipv4InterfaceContainer iic17 = ipv4.Assign (ndc17);

   Ptr<Ipv4StaticRouting> staticRouting;
   staticRouting = Ipv4RoutingHelper::GetRouting <Ipv4StaticRouting> (a->GetObject<Ipv4> ()->GetRoutingProtocol ());
   staticRouting->SetDefaultRoute ("10.0.0.2", 1 );  // R1
   staticRouting = Ipv4RoutingHelper::GetRouting <Ipv4StaticRouting> (k->GetObject<Ipv4> ()->GetRoutingProtocol ());
   staticRouting->SetDefaultRoute ("10.0.15.2", 1 );   // R2
   staticRouting = Ipv4RoutingHelper::GetRouting <Ipv4StaticRouting> (g->GetObject<Ipv4> ()->GetRoutingProtocol ());
   staticRouting->SetDefaultRoute ("10.0.7.2", 1 );
   staticRouting = Ipv4RoutingHelper::GetRouting <Ipv4StaticRouting> (h->GetObject<Ipv4> ()->GetRoutingProtocol ());
   staticRouting->SetDefaultRoute ("10.0.10.2", 1 );

 
   if (printRoutingTables)
     {
       RipHelper routingHelper;
 
       Ptr<OutputStreamWrapper> routingStream = Create<OutputStreamWrapper> (&std::cout);
 
       routingHelper.PrintRoutingTableAt (Seconds (10.0), r1, routingStream);
       routingHelper.PrintRoutingTableAt (Seconds (10.0), r2, routingStream);
       routingHelper.PrintRoutingTableAt (Seconds (10.0), r3, routingStream);
       routingHelper.PrintRoutingTableAt (Seconds (10.0), r4, routingStream);
       routingHelper.PrintRoutingTableAt (Seconds (10.0), r5, routingStream);
       routingHelper.PrintRoutingTableAt (Seconds (10.0), r6, routingStream);

       routingHelper.PrintRoutingTableAt (Seconds (40.0), r1, routingStream);
       routingHelper.PrintRoutingTableAt (Seconds (40.0), r2, routingStream);
       routingHelper.PrintRoutingTableAt (Seconds (40.0), r3, routingStream);
       routingHelper.PrintRoutingTableAt (Seconds (40.0), r4, routingStream);
       routingHelper.PrintRoutingTableAt (Seconds (40.0), r5, routingStream);
       routingHelper.PrintRoutingTableAt (Seconds (40.0), r6, routingStream);

       routingHelper.PrintRoutingTableAt (Seconds (80.0), r1, routingStream);
       routingHelper.PrintRoutingTableAt (Seconds (80.0), r2, routingStream);
       routingHelper.PrintRoutingTableAt (Seconds (80.0), r3, routingStream);
       routingHelper.PrintRoutingTableAt (Seconds (80.0), r4, routingStream);
       routingHelper.PrintRoutingTableAt (Seconds (80.0), r5, routingStream);
       routingHelper.PrintRoutingTableAt (Seconds (80.0), r6, routingStream);
 
       //routingHelper.PrintRoutingTableAt (Seconds (90.0), r1, routingStream);
       //routingHelper.PrintRoutingTableAt (Seconds (90.0), r2, routingStream);
       //routingHelper.PrintRoutingTableAt (Seconds (90.0), r3, routingStream);
       //routingHelper.PrintRoutingTableAt (Seconds (90.0), r4, routingStream);
       //routingHelper.PrintRoutingTableAt (Seconds (90.0), r5, routingStream);
      // routingHelper.PrintRoutingTableAt (Seconds (90.0), r6, routingStream);
     }
 
   NS_LOG_INFO ("Create Applications.");
   uint32_t packetSize = 1024;
   Time interPacketInterval = Seconds (1.0);
   V4PingHelper pingA ("10.0.15.1");
   // add changes here for parallel
   V4PingHelper pingB ("10.0.10.1");
 
   pingA.SetAttribute ("Interval", TimeValue (interPacketInterval));
   pingA.SetAttribute ("Size", UintegerValue (packetSize));
   pingB.SetAttribute ("Interval", TimeValue (interPacketInterval));
   pingB.SetAttribute ("Size", UintegerValue (packetSize));
   if (showPings)
     {
       pingA.SetAttribute ("Verbose", BooleanValue (true));
       pingB.SetAttribute ("Verbose", BooleanValue (true));

     }
   ApplicationContainer appsA = pingA.Install (a);
   appsA.Start (Seconds (1.0));
   appsA.Stop (Seconds (81.0));
   ApplicationContainer appsB = pingB.Install (g);
   appsB.Start (Seconds (1.0));
   appsB.Stop (Seconds (81.0));
 
   AsciiTraceHelper ascii;
   csma.EnableAsciiAll (ascii.CreateFileStream ("rip-simple-routing.tr"));
   csma.EnablePcapAll ("rip-simple-routing", true);
 
   Simulator::Schedule (Seconds (25), &TearDownLink, r3, r4, 2, 2);
 
   /* Now, do the actual simulation. */
   NS_LOG_INFO ("Run Simulation.");
   Simulator::Stop (Seconds (90.0));
   Simulator::Run ();
   Simulator::Destroy ();
   NS_LOG_INFO ("Done.");
 }
 

