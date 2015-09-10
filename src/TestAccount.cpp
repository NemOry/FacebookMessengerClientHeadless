#include <math.h>
#include <src/Utilities/Utilities.hpp>

#include "TestAccount.hpp"

#include <QDebug>

TestAccount::TestAccount(UDSUtil* udsUtil, HubCache* hubCache) : HubAccount(udsUtil, hubCache)
{
	qDebug()  << "TestAccount::TestAccount " << udsUtil;

	_categoryId = 0;

    _name                           = "Messenger";
    _displayName                    = "Messenger";
    _description                    = "";
    _serverName                     = "messenger.com";
    _iconFilename                   = "acc_uncolored.png";
    _lockedIconFilename             = "acc_locked_uncolored.png";
    _composeIconFilename            = "acc_compose_uncolored.png";
    _supportsCompose                = true;
    _supportsMarkRead               = true;
    _supportsMarkUnread             = true;
    _headlessTarget                 = "lcom.nemory.fbmessenger.headless";
    _appTarget                      = "lcom.nemory.fbmessenger";
    _cardTarget                     = "lcom.nemory.fbmessenger.hub.card";
    _itemMimeType                   = "hub/vnd.messenger.item";  // mime type for hub items - if you change this, adjust invocation targets
    _itemComposeIconFilename        = "acc_compose.png";
    _itemReadIconFilename           = "itemRead.png";
    _itemUnreadIconFilename         = "itemUnread.png";
    _markReadActionIconFilename     = "itemMarkRead.png";
    _markUnreadActionIconFilename   = "itemMarkUnread.png";

    // on device restart / update, it may be necessary to reload the Hub
    if (_udsUtil->reloadHub())
    {
        _udsUtil->cleanupAccountsExcept(-1, _displayName);
        _udsUtil->initNextIds();
    }

    initialize();

    QVariantList categories;
    QVariantMap category;
    category["categoryId"] = 1; // categories are created with sequential category Ids starting at 1 so number your predefined categories
                                // accordingly
    category["name"] = "Inbox";
    category["parentCategoryId"] = 0; // default parent category ID for root categories
    categories << category;
    initializeCategories(categories);

    // reload existing hub items if required
    if (_udsUtil->reloadHub()) {
        repopulateHub();

        _udsUtil->resetReloadHub();
    }
}

TestAccount::~TestAccount()
{
}

qint64 TestAccount::accountId()
{
    return _accountId;
}

qint64 TestAccount::categoryId()
{
    return _categoryId;
}

void TestAccount::initializeCategories(QVariantList newCategories)
{
    HubAccount::initializeCategories(newCategories);

    if (_categoriesInitialized) {
        // initialize category ID - we are assuming that we only added one category
        QVariantList categories = _hubCache->categories();

        _categoryId = categories[0].toMap()["categoryId"].toLongLong();
    }
}
