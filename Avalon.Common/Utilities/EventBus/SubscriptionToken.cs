using System;

namespace Avalon.Common.Utilities.EventBus
{
    /// <summary>
    /// A Token representing a Subscription
    /// </summary>
    public class SubscriptionToken
    {
        internal SubscriptionToken(Type eventItemType)
        {
            Token = Guid.NewGuid();
            EventItemType = eventItemType;
        }

        public Guid Token { get; }
        public Type EventItemType { get; }
    }
}