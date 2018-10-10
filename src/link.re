let component = ReasonReact.statelessComponent("Link");

let handleClick = (href, event) =>
  if (!ReactEvent.Mouse.defaultPrevented(event)) {
    ReactEvent.Mouse.preventDefault(event);
    ReasonReact.Router.push(href);
  };

let make = (~href, ~className="", children) => {
  ...component,
  render: self =>
    <a
      href
      className
      onClick={self.handle((event, _) => handleClick(href, event))}>
      ...children
    </a>,
};