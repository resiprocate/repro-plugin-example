
#include "rutil/Logger.hxx"
#include "resip/stack/Helper.hxx"
#include "repro/Plugin.hxx"
#include "repro/Processor.hxx"
#include "repro/RequestContext.hxx"

#define RESIPROCATE_SUBSYSTEM resip::Subsystem::REPRO

using namespace resip;
using namespace repro;

class ExamplePlugin : public Plugin, public Processor
{
   public:
      ExamplePlugin()  : Processor("Example") {};
      ~ExamplePlugin(){};

      virtual bool init(SipStack& sipStack, ProxyConfig *proxyConfig)
      {
          DebugLog(<<"ExamplePlugin: init called");
          return true;
      }

      virtual void onRequestProcessorChainPopulated(ProcessorChain& chain)
      {
         DebugLog(<<"ExamplePlugin: onRequestProcessorChainPopulated called");

         // The module class is also the monkey class, no need to create
         // any monkey instance here, just add ourself to the chain

         // Add the example monkey to the chain
         chain.addProcessor(std::auto_ptr<Processor>(this));
      }

      virtual void onResponseProcessorChainPopulated(ProcessorChain& chain)
      {
         DebugLog(<<"ExamplePlugin: onResponseProcessorChainPopulated called");
      }

      virtual void onTargetProcessorChainPopulated(ProcessorChain& chain)
      {
         DebugLog(<<"ExamplePlugin: onTargetProcessorChainPopulated called");
      }

      /*
       * Now we implement the Processor API from repro/Processor.hxx
       * We are called from the request processor chain, that makes
       * this class a monkey in the reSIProcate/repro terminology
       */

      virtual processor_action_t process(RequestContext &context)
      {
         DebugLog(<< "Monkey handling request: ExamplePlugin");

         SipMessage& msg = context.getOriginalRequest();

         // Barf if the SIP message uses the MESSAGE method
         if(msg.method() == MESSAGE)
         {
            context.sendResponse(*std::auto_ptr<SipMessage>
               (Helper::makeResponse(msg, 500, "Internal error")));
            return SkipAllChains;
         }
         return Processor::Continue;
      }

};


extern "C" {

static
Plugin* instantiate()
{
   return new ExamplePlugin();
}

ReproPluginDescriptor reproPluginDesc =
{
   REPRO_DSO_PLUGIN_API_VERSION,
   &instantiate
};

};

/* ====================================================================
 *
 * Copyright 2013 Daniel Pocock http://danielpocock.com  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. Neither the name of the author(s) nor the names of any contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR(S) AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR(S) OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * ====================================================================
 *
 *
 */

