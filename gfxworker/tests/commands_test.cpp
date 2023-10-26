#include "gtest/gtest.h"
#include "mega/gfx/worker/comms.h"
#include "mega/gfx/worker/commands.h"
#include "mega/gfx/worker/command_serializer.h"

using mega::gfx::CommandSerializer;
using mega::gfx::CommandNewGfx;
using mega::gfx::CommandNewGfxResponse;
using mega::gfx::CommandShutDown;
using mega::gfx::CommandShutDownResponse;
using mega::gfx::CommandHello;
using mega::gfx::CommandHelloResponse;
using mega::gfx::CommandSupportFormats;
using mega::gfx::CommandSupportFormatsResponse;
using mega::gfx::TimeoutMs;
using mega::gfx::IReader;
using mega::GfxDimension;

namespace mega
{
namespace gfx
{
    bool operator==(const CommandNewGfx& lhs, const CommandNewGfx& rhs)
    {
        return lhs.Task.Path == rhs.Task.Path && lhs.Task.Dimensions == rhs.Task.Dimensions;
    }

    bool operator==(const CommandNewGfxResponse& lhs, const CommandNewGfxResponse& rhs)
    {
        return lhs.ErrorCode == rhs.ErrorCode && lhs.ErrorText == rhs.ErrorText && lhs.Images == rhs.Images;
    }

    bool operator==(const CommandShutDown& /*lhs*/, const CommandShutDown& /*rhs*/)
    {
        return true;
    }

    bool operator==(const CommandShutDownResponse& /*lhs*/, const CommandShutDownResponse& /*rhs*/)
    {
        return true;
    }

    bool operator==(const CommandHello& lhs, const CommandHello& rhs)
    {
        return lhs.Text == rhs.Text;
    }

    bool operator==(const CommandHelloResponse& lhs, const CommandHelloResponse& rhs)
    {
        return lhs.Text == rhs.Text;
    }

    bool operator==(const CommandSupportFormats& /*lhs*/, const CommandSupportFormats& /*rhs*/)
    {
        return true;
    }

    bool operator==(const CommandSupportFormatsResponse& lhs, const CommandSupportFormatsResponse& rhs)
    {
        return lhs.formats == rhs.formats && lhs.videoformats == rhs.videoformats;
    }
}
}

class StringReader : public IReader
{
public:
    StringReader(std::string&& value) : mValue(std::move(value)), mIndex{0} {}
private:
    bool do_read(void* out, size_t n, TimeoutMs timeout) override;

    std::string mValue;
    size_t      mIndex;
};

bool StringReader::do_read(void* out, size_t n, TimeoutMs /*timeout*/)
{
    if (mIndex > mValue.size()) return false;

    if (mIndex + n > mValue.size()) return false;

    std::memcpy(out, mValue.data() + mIndex, n);

    mIndex += n;

    return true;
}

TEST(CommandSerializer, CommandNewGfxSerializeAndUnserializeSuccessfully)
{
    CommandNewGfx sourceCommand;
    sourceCommand.Task.Path = "c:\\path\\image.png";
    sourceCommand.Task.Dimensions = std::vector<GfxDimension>{ {250, 0} };

    auto data = CommandSerializer::serialize(&sourceCommand);
    ASSERT_NE(data, nullptr);

    StringReader reader(std::move(*data));
    auto command = CommandSerializer::unserialize(reader, TimeoutMs(5000));
    ASSERT_NE(command, nullptr);
    auto targetCommand = dynamic_cast<CommandNewGfx*>(command.get());
    ASSERT_NE(targetCommand, nullptr);
    ASSERT_EQ(sourceCommand, *targetCommand);
}

TEST(CommandSerializer, CommandNewGfxResponseSerializeAndUnserializeSuccessfully)
{
    CommandNewGfxResponse sourceCommand;
    sourceCommand.ErrorCode = 0;
    sourceCommand.ErrorText = "OK";
    sourceCommand.Images.push_back("imagedata");

    auto data = CommandSerializer::serialize(&sourceCommand);
    ASSERT_NE(data, nullptr);

    StringReader reader(std::move(*data));
    auto command = CommandSerializer::unserialize(reader, TimeoutMs(5000));
    ASSERT_NE(command, nullptr);
    auto targetCommand = dynamic_cast<CommandNewGfxResponse*>(command.get());
    ASSERT_NE(targetCommand, nullptr);
    ASSERT_EQ(sourceCommand, *targetCommand);
}

TEST(CommandSerializer, CommandShutdownSerializeAndUnserializeSuccessfully)
{
    CommandShutDown sourceCommand;

    auto data = CommandSerializer::serialize(&sourceCommand);
    ASSERT_NE(data, nullptr);

    StringReader reader(std::move(*data));
    auto command = CommandSerializer::unserialize(reader, TimeoutMs(5000));
    ASSERT_NE(command, nullptr);
    auto targetCommand = dynamic_cast<CommandShutDown*>(command.get());
    ASSERT_NE(targetCommand, nullptr);
    ASSERT_EQ(sourceCommand, *targetCommand);
}

TEST(CommandSerializer, CommandShutdownResponseSerializeAndUnserializeSuccessfully)
{
    CommandShutDownResponse sourceCommand;

    auto data = CommandSerializer::serialize(&sourceCommand);
    ASSERT_NE(data, nullptr);

    StringReader reader(std::move(*data));
    auto command = CommandSerializer::unserialize(reader, TimeoutMs(5000));
    ASSERT_NE(command, nullptr);
    auto targetCommand = dynamic_cast<CommandShutDownResponse*>(command.get());
    ASSERT_NE(targetCommand, nullptr);
    ASSERT_EQ(sourceCommand, *targetCommand);
}

TEST(CommandSerializer, CommandHelloSerializeAndUnserializeSuccessfully)
{
    CommandHello sourceCommand;

    auto data = CommandSerializer::serialize(&sourceCommand);
    ASSERT_NE(data, nullptr);

    StringReader reader(std::move(*data));
    auto command = CommandSerializer::unserialize(reader, TimeoutMs(5000));
    ASSERT_NE(command, nullptr);
    auto targetCommand = dynamic_cast<CommandHello*>(command.get());
    ASSERT_NE(targetCommand, nullptr);
    ASSERT_EQ(sourceCommand, *targetCommand);
}

TEST(CommandSerializer, CommandHelloResponseSerializeAndUnserializeSuccessfully)
{
    CommandHelloResponse sourceCommand;

    auto data = CommandSerializer::serialize(&sourceCommand);
    ASSERT_NE(data, nullptr);

    StringReader reader(std::move(*data));
    auto command = CommandSerializer::unserialize(reader, TimeoutMs(5000));
    ASSERT_NE(command, nullptr);
    auto targetCommand = dynamic_cast<CommandHelloResponse*>(command.get());
    ASSERT_NE(targetCommand, nullptr);
    ASSERT_EQ(sourceCommand, *targetCommand);
}

TEST(CommandSerializer, CommandSupportFormatsSerializeAndUnserializeSuccessfully)
{
    CommandSupportFormats sourceCommand;

    auto data = CommandSerializer::serialize(&sourceCommand);
    ASSERT_NE(data, nullptr);

    StringReader reader(std::move(*data));
    auto command = CommandSerializer::unserialize(reader, TimeoutMs(5000));
    ASSERT_NE(command, nullptr);
    auto targetCommand = dynamic_cast<CommandSupportFormats*>(command.get());
    ASSERT_NE(targetCommand, nullptr);
    ASSERT_EQ(sourceCommand, *targetCommand);
}

TEST(CommandSerializer, CommandSupportFormatsResponseSerializeAndUnserializeSuccessfully)
{
    CommandSupportFormatsResponse sourceCommand;

    auto data = CommandSerializer::serialize(&sourceCommand);
    ASSERT_NE(data, nullptr);

    StringReader reader(std::move(*data));
    auto command = CommandSerializer::unserialize(reader, TimeoutMs(5000));
    ASSERT_NE(command, nullptr);
    auto targetCommand = dynamic_cast<CommandSupportFormatsResponse*>(command.get());
    ASSERT_NE(targetCommand, nullptr);
    ASSERT_EQ(sourceCommand, *targetCommand);
}
